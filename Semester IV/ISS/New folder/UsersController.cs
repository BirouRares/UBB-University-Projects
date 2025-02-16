using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Server.DTOs;
using Server.DatabaseContext;
using System.Xml.Linq;
using Server.Utils;

namespace Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class UsersController : ControllerBase
    {
        private readonly ProjectDBContext context;

        public UsersController(ProjectDBContext context)
        {
            this.context = context;
        }

        // GET: api/Users
        [HttpGet]
        public async Task<ActionResult<IEnumerable<UserDTO>>> GetUserDTO()
        {
            return await context.Users.Select(element => BaseToDTOConverters.Converter_UserToDTO(element)).ToListAsync();
        }

        // GET: api/Users/5
        [HttpGet("{id}")]
        public async Task<ActionResult<UserDTO>> GetUser(int id)
        {
            var user = await context.Users.FindAsync(id);

            if (user == null)
            {
                return NotFound();
            }

            return BaseToDTOConverters.Converter_UserToDTO(user);
        }

        // PUT: api/Users/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutUser(int id, UserDTO user)
        {
            if (id != user.Id)
            {
                return BadRequest();
            }
            var userRef = DTOToBaseConverters.Converter_DTOToUser(user);
            context.Entry(userRef).State = EntityState.Modified;

            try
            {
                await context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!UserExists(id))
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

        // POST: api/Users
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<UserDTO>> PostUser(UserDTO user)
        {
            var userRef = DTOToBaseConverters.Converter_DTOToUser(user);
            context.Users.Add(userRef);
            await context.SaveChangesAsync();

            user.Id = userRef.Id;
            return CreatedAtAction("GetUserDTO", new { id = user.Id }, user);
        }

        // DELETE: api/Users/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteUser(int id)
        {
            var user = await context.Users.FindAsync(id);
            if (user == null)
            {
                return NotFound();
            }

            context.Users.Remove(user);
            await context.SaveChangesAsync();

            return NoContent();
        }

        private bool UserExists(int id)
        {
            return context.Users.Any(e => e.Id == id);
        }
    }
}
