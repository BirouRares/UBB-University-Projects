using System;
using System.Buffers.Text;
using System.Reflection.Metadata;

namespace rt
{
    class RayTracer
    {
        private readonly Geometry[] _geometries;
        private readonly Light[] _lights;

        public RayTracer(Geometry[] geometries, Light[] lights)
        {
            _geometries = geometries;
            _lights = lights;
        }

        private double ImageToViewPlane(int coordinate, int imageSize, double viewPlaneSize)
        { //Converts a pixel coordinate from image space to view plane space
            return -coordinate * viewPlaneSize / imageSize + viewPlaneSize / 2;
        } // maps pixel positions(image space) to positions on the view plane (real-world space).

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            Intersection closestIntersection = Intersection.NONE;

            foreach (var geometry in _geometries)
            {
                var intersection = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intersection.Valid || !intersection.Visible)
                {
                    continue;
                }

                if (!closestIntersection.Valid || !closestIntersection.Visible || intersection.T < closestIntersection.T)
                {
                    closestIntersection = intersection;
                }
            }

            return closestIntersection;
        }

        private bool IsLit(Vector point, Light light)
        { //Determines whether a point on a surface is lit by a specific light source or blocked
            const double Epsilon = 1e-10;
            var incidentLine = new Line(point, light.Position);
            var segmentLength = (point - light.Position).Length();

            foreach (var geometry in _geometries)
            {
                if (geometry is RawCtMask) continue; // Ignore the RawCtMask geometry

                var intersection = geometry.GetIntersection(incidentLine, Epsilon, segmentLength, true);

                if (intersection.Visible)
                {
                    return false;
                }
            }

            return true;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var backgroundColor = new Color(0.2, 0.2, 0.2, 1.0);
            var viewParallel = (camera.Up ^ camera.Direction).Normalize(); //view direction vector, parallel(^) to the view plane
            //perpendicular to view up for camera and parelel to camera direction
            var viewDirection = camera.Direction * camera.ViewPlaneDistance; //Direction in which the camera is looking(view direction) *=>perpendicular
            var renderedImage = new Image(width, height);

            for (var i = 0; i < width; i++) //Iterate over all pixels in the image
            {
                var viewPlaneX = ImageToViewPlane(i, width, camera.ViewPlaneWidth);// idst from left edge of the view plane

                for (var j = 0; j < height; j++)
                {
                    var viewPlaneY = ImageToViewPlane(j, height, camera.ViewPlaneHeight); // dist from bottom edge of the view plane
                    var rayVector = camera.Position +
                                    viewDirection +
                                    viewParallel * viewPlaneX + //moving on the horizontal axis based on the pixel position
                                    camera.Up * viewPlaneY; //moving on the vertical axis based on the pixel position

                    var ray = new Line(camera.Position, rayVector);
                    var intersection = FindFirstIntersection(ray, camera.FrontPlaneDistance, camera.BackPlaneDistance); // find intersections

                    if (!intersection.Visible)
                    {
                        renderedImage.SetPixel(i, j, backgroundColor);
                        continue;
                    }

                    var pixelColor = CalculatePixelColor(intersection, camera.Position);
                    renderedImage.SetPixel(i, j, pixelColor);
                }
            }

            renderedImage.Store(filename);
        }

        private Color CalculatePixelColor(Intersection intersection, Vector cameraPosition)
        {
            var pixelColor = new Color();
            var material = intersection.Material;
            var pointOnSurface = intersection.Position;
            var surfaceNormal = intersection.Normal;
            var eyeVector = (cameraPosition - pointOnSurface).Normalize();
            /*Ambient Light: General scene illumination.
              Diffuse Light: Light scattered from the surface based on the angle of incidence.
              Specular Light: Highlights due to light reflecting toward the camera.*/



            foreach (var light in _lights) // Iterate over all light sources
            {
                var ambientComponent = material.Ambient * light.Ambient;
                pixelColor += ambientComponent;

                if (!IsLit(pointOnSurface, light)) continue; // if not lit, skip

                var lightDirection = (light.Position - pointOnSurface).Normalize();
                var reflectionDirection = (surfaceNormal * (surfaceNormal * lightDirection) * 2 - lightDirection).Normalize();

                var diffuseFactor = Math.Max(0, surfaceNormal * lightDirection); // dot product 
                if (diffuseFactor > 0) //the surface is facing the light
                {
                    var diffuseComponent = material.Diffuse * light.Diffuse * diffuseFactor; // Diffuse reflection
                    pixelColor += diffuseComponent;
                }

                var specularFactor = Math.Max(0, eyeVector * reflectionDirection); // dot product => intensity, higher => closer
                if (specularFactor > 0)
                {
                    var specularComponent = material.Specular * light.Specular * Math.Pow(specularFactor, material.Shininess);
                    pixelColor += specularComponent; // Specular reflection
                }

                pixelColor *= light.Intensity;
            }

            return pixelColor;
        }
    }
}
