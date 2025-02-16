using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Server.DTOs;
using Server.DatabaseContext;
using Server.Utils;

namespace Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class MediasController : ControllerBase
    {
        private readonly ProjectDBContext context;

        public MediasController(ProjectDBContext context)
        {
            this.context = context;
        }

        // GET: api/Media
        [HttpGet]
        public async Task<ActionResult<IEnumerable<MediaDTO>>> GetMedias()
        {
            return await context.Medias.Select(element => BaseToDTOConverters.Converter_MediaToDTO(element)).ToListAsync();
        }

        // GET: api/Media/5
        [HttpGet("{id}")]
        public async Task<ActionResult<MediaDTO>> GetMedia(int id)
        {
            var media = await context.Medias.FindAsync(id);

            if (media == null)
            {
                return NotFound();
            }

            return BaseToDTOConverters.Converter_MediaToDTO(media);
        }

        // PUT: api/Media/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutMedia(int id, MediaDTO media)
        {
            if (id != media.Id)
            {
                return BadRequest();
            }

            var mediaRef = DTOToBaseConverters.Converter_DTOToMedia(media);
            context.Entry(mediaRef).State = EntityState.Modified;

            try
            {
                await context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!MediaExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/Media
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<MediaDTO>> PostMedia(MediaDTO media)
        {
            var mediaRef = DTOToBaseConverters.Converter_DTOToMedia(media);
            context.Medias.Add(mediaRef);
            await context.SaveChangesAsync();

            return CreatedAtAction("GetMedia", new { id = media.Id }, media);
        }

        // DELETE: api/Media/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteMedia(int id)
        {
            var media = await context.Medias.FindAsync(id);
            if (media == null)
            {
                return NotFound();
            }

            context.Medias.Remove(media);
            await context.SaveChangesAsync();

            return NoContent();
        }

        private bool MediaExists(int id)
        {
            return context.Medias.Any(e => e.Id == id);
        }
    }
}
