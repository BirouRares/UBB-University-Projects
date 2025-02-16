using Microsoft.EntityFrameworkCore;
using Server.Models;
using Server.DTOs;

namespace Server.DatabaseContext
{
    public class ProjectDBContext : DbContext
    {
        public ProjectDBContext(DbContextOptions<ProjectDBContext> options) : base(options)
        {
        }

        public DbSet<Location> Locations { get; set; } = null!;
        public DbSet<Media> Medias { get; set; } = null!;
        public DbSet<User> Users { get; set; } = null!;
        public DbSet<Server.DTOs.MediaDTO> MediaDTO { get; set; } = default!;
    }
}
