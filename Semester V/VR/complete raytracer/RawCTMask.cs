using rt;
using System;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace rt
{
    public class RawCtMask : Geometry
    {
        private readonly Vector _position; // Lower-left corner position
        private readonly double _scale; // Scale factor applied to the voxel data for visualization
        private readonly ColorMap _colorMap; // Color mapping
        private readonly byte[] _data; // Raw voxel(a three-dimensional counterpart to a pixel) data

        private readonly int[] _resolution = new int[3]; // Voxel resolution
        private readonly double[] _thickness = new double[3]; // Voxel thickness in mm
        private readonly Ellipsoid _boundingEllipsoid; // Bounding ellipsoid

        private const double Epsilon = 1e-10;

        public RawCtMask(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap)
            : base(Color.NONE)
        {
            _position = position;
            _scale = scale;
            _colorMap = colorMap;

            ParseDatFile(datFile);
            _data = LoadRawData(rawFile);
            _boundingEllipsoid = CreateBoundingEllipsoid();
        }

        private void ParseDatFile(string datFile)
        {
            foreach (var line in File.ReadLines(datFile))
            {
                var keyValue = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
                if (keyValue.Length < 4) continue;

                switch (keyValue[0])
                {
                    case "Resolution":
                        for (int i = 0; i < 3; i++) _resolution[i] = int.Parse(keyValue[i + 1]);
                        break;
                    case "SliceThickness":
                        for (int i = 0; i < 3; i++) _thickness[i] = double.Parse(keyValue[i + 1]);
                        break;
                }
            }
        }

        private byte[] LoadRawData(string rawFile)
        {
            int totalVoxels = _resolution[0] * _resolution[1] * _resolution[2];
            var rawData = new byte[totalVoxels];

            using var fileStream = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
            int bytesRead = fileStream.Read(rawData, 0, totalVoxels);

            if (bytesRead != totalVoxels)
            {
                throw new InvalidDataException($"Expected {totalVoxels} bytes, but only read {bytesRead} bytes from {rawFile}");
            }

            return rawData;
        }

        private Ellipsoid CreateBoundingEllipsoid()
        {
            var diagonal = new Vector(
                _resolution[0] * _thickness[0] * _scale,
                _resolution[1] * _thickness[1] * _scale,
                _resolution[2] * _thickness[2] * _scale
            );

            var center = _position + (diagonal / 2);
            return new Ellipsoid(center, diagonal / 2, 1, Color.NONE);
        }

        private ushort GetVoxelValue(int x, int y, int z)
        {
            if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2])
            {
                return 0;
            }

            return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist, bool? onlyFirst = false)
        {
            var (t1, t2) = _boundingEllipsoid.GetFirstAndLastIntersection(line);

            if (t1 == null || t2 == null) return Intersection.NONE;

            double start = Math.Max(t1.Value, minDist);// valid range of intersection within the specified distance range
            double end = Math.Min(t2.Value, maxDist);

            double stepSize = _scale; // size for sampling the intersection points
            bool passedFirst = false;  // check if we have passed the first intersection
            double firstIntersection = 0;  // get the value first intersection point
            Vector normal = new Vector(); // normal vector, no normal => no lightings
            Color accumulatedColor = new Color(); // accumulated color during ray traversal
            double remainingAlpha = 1; // the value for transparency

            for (double t = start; t <= end; t += stepSize)
            {
                var point = line.CoordinateToPosition(t); // Compute 3D position along the ray
                var voxelIndices = GetVoxelIndices(point); // Convert position to voxel indices // Get voxel color based on indices
                var voxelColor = GetVoxelColor(voxelIndices);

                if (voxelColor.Alpha == 0) continue; // if transparent, skip

                if (!passedFirst)
                {
                    firstIntersection = t; //distance along the ray
                    normal = GetNormal(voxelIndices);
                    passedFirst = true;

                    if (onlyFirst == true) // only if the first intersection is required
                    {
                        return new Intersection(true, true, this, line, t, normal, Material, Color.NONE);
                    }
                }

                accumulatedColor += voxelColor * voxelColor.Alpha * remainingAlpha;
                remainingAlpha *= 1 - voxelColor.Alpha;

                if (remainingAlpha < Epsilon) break;
            }

            if (!passedFirst) return Intersection.NONE; //no intersaction funcd

            return new Intersection(
                true,
                passedFirst,
                this,
                line,
                firstIntersection,
                normal,
                Material.FromColor(accumulatedColor),
                accumulatedColor
            );
        }

        private int[] GetVoxelIndices(Vector point)
        { //Converts a 3D point into voxel grid indices
            return new[]
            {
                (int)Math.Floor((point.X - _position.X) / (_thickness[0] * _scale)),
                (int)Math.Floor((point.Y - _position.Y) / (_thickness[1] * _scale)),
                (int)Math.Floor((point.Z - _position.Z) / (_thickness[2] * _scale))
            };
        }

        private Color GetVoxelColor(int[] indices)
        { //Retrieves the color of a voxel using its intensity value mapped through _colorMap
            ushort value = GetVoxelValue(indices[0], indices[1], indices[2]);
            return _colorMap.GetColor(value);
        }

        private Vector GetNormal(int[] indices)
        {
            double x0 = GetVoxelValue(indices[0] - 1, indices[1], indices[2]);
            double x1 = GetVoxelValue(indices[0] + 1, indices[1], indices[2]);
            double y0 = GetVoxelValue(indices[0], indices[1] - 1, indices[2]);
            double y1 = GetVoxelValue(indices[0], indices[1] + 1, indices[2]);
            double z0 = GetVoxelValue(indices[0], indices[1], indices[2] - 1);
            double z1 = GetVoxelValue(indices[0], indices[1], indices[2] + 1);

            return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
        }
    }
}
