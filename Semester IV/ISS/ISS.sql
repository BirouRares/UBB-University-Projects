-- Create the database
CREATE DATABASE [blank-feed]
CONTAINMENT = NONE
ON PRIMARY 
(
    NAME = N'blank-feed', 
    FILENAME = N'D:\facultate\Sem_4\ISS\blank-feed.mdf', 
    SIZE = 8192KB , 
    MAXSIZE = UNLIMITED, 
    FILEGROWTH = 65536KB 
)
LOG ON 
(
    NAME = N'blank-feed_log', 
    FILENAME = N'D:\facultate\Sem_4\ISS\blank-feed_log.ldf', 
    SIZE = 8192KB , 
    MAXSIZE = 2048GB , 
    FILEGROWTH = 65536KB 
)
GO

-- Set compatibility level
ALTER DATABASE [blank-feed] SET COMPATIBILITY_LEVEL = 150
GO

-- Enable Full-Text Search if installed
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
BEGIN
    EXEC [blank-feed].[dbo].[sp_fulltext_database] @action = 'enable'
END
GO

-- Set database options
ALTER DATABASE [blank-feed] SET ANSI_NULL_DEFAULT OFF 
ALTER DATABASE [blank-feed] SET ANSI_NULLS OFF 
ALTER DATABASE [blank-feed] SET ANSI_PADDING OFF 
ALTER DATABASE [blank-feed] SET ANSI_WARNINGS OFF 
ALTER DATABASE [blank-feed] SET ARITHABORT OFF 
ALTER DATABASE [blank-feed] SET AUTO_CLOSE OFF 
ALTER DATABASE [blank-feed] SET AUTO_SHRINK OFF 
ALTER DATABASE [blank-feed] SET AUTO_UPDATE_STATISTICS ON 
ALTER DATABASE [blank-feed] SET CURSOR_CLOSE_ON_COMMIT OFF 
ALTER DATABASE [blank-feed] SET CURSOR_DEFAULT GLOBAL 
ALTER DATABASE [blank-feed] SET CONCAT_NULL_YIELDS_NULL OFF 
ALTER DATABASE [blank-feed] SET NUMERIC_ROUNDABORT OFF 
ALTER DATABASE [blank-feed] SET QUOTED_IDENTIFIER OFF 
ALTER DATABASE [blank-feed] SET RECURSIVE_TRIGGERS OFF 
ALTER DATABASE [blank-feed] SET ENABLE_BROKER 
ALTER DATABASE [blank-feed] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
ALTER DATABASE [blank-feed] SET DATE_CORRELATION_OPTIMIZATION OFF 
ALTER DATABASE [blank-feed] SET TRUSTWORTHY OFF 
ALTER DATABASE [blank-feed] SET ALLOW_SNAPSHOT_ISOLATION OFF 
ALTER DATABASE [blank-feed] SET PARAMETERIZATION SIMPLE 
ALTER DATABASE [blank-feed] SET READ_COMMITTED_SNAPSHOT OFF 
ALTER DATABASE [blank-feed] SET HONOR_BROKER_PRIORITY OFF 
ALTER DATABASE [blank-feed] SET RECOVERY SIMPLE 
ALTER DATABASE [blank-feed] SET MULTI_USER 
ALTER DATABASE [blank-feed] SET PAGE_VERIFY CHECKSUM  
ALTER DATABASE [blank-feed] SET DB_CHAINING OFF 
ALTER DATABASE [blank-feed] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
ALTER DATABASE [blank-feed] SET TARGET_RECOVERY_TIME = 60 SECONDS 
ALTER DATABASE [blank-feed] SET DELAYED_DURABILITY = DISABLED 
ALTER DATABASE [blank-feed] SET ACCELERATED_DATABASE_RECOVERY = OFF  
ALTER DATABASE [blank-feed] SET QUERY_STORE = OFF
GO

-- Use the newly created database
USE [blank-feed]
GO

-- Create tables
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[configurations](
	[allowedFileExtensions] [ntext] NULL,
	[maxFileSize] [int] NULL,
	[GOOGLE_PLACES_API_KEY] [text] NULL,
	[ENCRYPTION_KEY] [text] NULL
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[hashtags](
	[hashtag_id] [varchar](36) NOT NULL,
	[name] [varchar](50) NOT NULL,
 CONSTRAINT [PK_hashtags] PRIMARY KEY CLUSTERED 
(
	[hashtag_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO


SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[logs](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Message] [nvarchar](max) NULL,
	[MessageTemplate] [nvarchar](max) NULL,
	[Level] [nvarchar](max) NULL,
	[TimeStamp] [datetime] NULL,
	[Exception] [nvarchar](max) NULL,
	[Properties] [nvarchar](max) NULL,
 CONSTRAINT [PK_logs] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO

-- Create other tables similarly

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[mentions](
	[post_id] [varchar](36) NULL,
	[user_id] [varchar](36) NULL
) ON [PRIMARY]
GO


SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[post_archive](
	[archive_id] [varchar](36) NOT NULL,
	[post_id] [varchar](36) NULL,
 CONSTRAINT [PK_post_archive] PRIMARY KEY CLUSTERED 
(
	[archive_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO


SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[post_hashtags](
	[post_id] [varchar](36) NULL,
	[hashtag_id] [varchar](36) NULL
) ON [PRIMARY]
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[post_reports](
	[report_id] [varchar](36) NOT NULL,
	[reason] [text] NULL,
	[description] [text] NULL,
	[post_id] [varchar](36) NULL,
	[reporter_id] [varchar](36) NULL,
 CONSTRAINT [PK_post_reports] PRIMARY KEY CLUSTERED 
(
	[report_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[post_saves]    Script Date: 4/21/2024 4:40:25 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[post_saves](
	[save_id] [varchar](36) NOT NULL,
	[post_id] [varchar](36) NULL,
	[user_id] [varchar](36) NULL,
 CONSTRAINT [PK_post_saves] PRIMARY KEY CLUSTERED 
(
	[save_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[posts]    Script Date: 4/21/2024 4:40:25 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[posts](
	[post_id] [varchar](36) NOT NULL,
	[owner_user_id] [varchar](36) NOT NULL,
	[description] [text] NULL,
	[commented_post_id] [varchar](36) NULL,
	[original_post_id] [varchar](36) NULL,
	[media_path] [text] NULL,
	[post_type] [smallint] NOT NULL,
	[location_id] [nchar](27) NULL,
	[created_date] [datetime] NOT NULL,
 CONSTRAINT [PK_posts] PRIMARY KEY CLUSTERED 
(
	[post_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[reactions]    Script Date: 4/21/2024 4:40:25 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[reactions](
	[post_id] [varchar](36) NULL,
	[user_id] [varchar](36) NULL,
	[reaction] [smallint] NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[users]    Script Date: 4/21/2024 4:40:25 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[users](
	[user_id] [varchar](36) NOT NULL,
	[username] [varchar](36) NULL,
	[profile_pic_path] [varchar](1000) NULL,
 CONSTRAINT [PK_users] PRIMARY KEY CLUSTERED 
(
	[user_id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO


-- Data insertion
INSERT [dbo].[configurations] ([allowedFileExtensions], [maxFileSize], [GOOGLE_PLACES_API_KEY], [ENCRYPTION_KEY]) VALUES (N'.jpg .jpeg .png .gif .mp4 .avi .mov .mkv', 50, N'AIzaSyB0sAUSRfZHPS6jKzyjPDaeakE8IIxIom4', N'80-D0-C4-C7-7D-2A-29-0F-2C-0D-D8-2C-D5-AD-65-38-E4-26-35-76-7C-09-0D-32-91-62-B8-9E-D7-31-5A-95')
GO
SET IDENTITY_INSERT [dbo].[logs] ON 

INSERT [dbo].[logs] ([Id], [Message], [MessageTemplate], [Level], [TimeStamp], [Exception], [Properties]) VALUES (1, N'start', N'start', N'Information', CAST(N'2024-04-09T21:22:56.603' AS DateTime), NULL, N'<properties><property key=''SourceContext''>client.App</property></properties>')
INSERT [dbo].[logs] ([Id], [Message], [MessageTemplate], [Level], [TimeStamp], [Exception], [Properties]) VALUES (2, N'start', N'start', N'Information', CAST(N'2024-04-09T21:25:09.507' AS DateTime), NULL, N'<properties><property key=''SourceContext''>client.App</property></properties>')
SET IDENTITY_INSERT [dbo].[logs] OFF
GO
INSERT [dbo].[mentions] ([post_id], [user_id]) VALUES (N'F4E08545-F179-4AD6-BB5D-C7F802EE6814', N'D5711B72-7E1F-4A8D-9226-38F6DA717A77')
INSERT [dbo].[mentions] ([post_id], [user_id]) VALUES (N'F4E08545-F179-4AD6-BB5D-C7F802EE6814', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77')
INSERT [dbo].[mentions] ([post_id], [user_id]) VALUES (N'8F8A147A-5B80-47E9-A092-A675F439A515', N'D5711B72-7E1F-4A8D-9226-38F6DA717A77')
INSERT [dbo].[mentions] ([post_id], [user_id]) VALUES (N'8EB731DD-07DC-41DB-A576-6AB50C326EA4', N'D5711B72-7E1F-4A8D-9226-38F6DA717A77')
GO
INSERT [dbo].[post_archive] ([archive_id], [post_id]) VALUES (N'68F5F264-9A28-4BD6-B30B-F293D29E3D90', N'BDF1733F-615C-40CA-9D40-2E65369B911F')
INSERT [dbo].[post_archive] ([archive_id], [post_id]) VALUES (N'C246EA51-5BB6-4739-BE18-1923F4A57787', N'8EB731DD-07DC-41DB-A576-6AB50C326EA4')
GO
INSERT [dbo].[post_reports] ([report_id], [reason], [description], [post_id], [reporter_id]) VALUES (N'61B8452B-2F33-4672-AB3F-E92B1252C6E8', N'Abusive', N'This is how you report a post', N'8EB731DD-07DC-41DB-A576-6AB50C326EA4', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77')
INSERT [dbo].[post_reports] ([report_id], [reason], [description], [post_id], [reporter_id]) VALUES (N'6B45FE23-3A23-400F-A167-B854E0A3640A', N'Abusive', N'M-a abuzat', N'8EB731DD-07DC-41DB-A576-6AB50C326EA4', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77')
GO
INSERT [dbo].[post_saves] ([save_id], [post_id], [user_id]) VALUES (N'E1F4E708-FBE7-4067-AA6B-DF9676A28C9F', N'8EB731DD-07DC-41DB-A576-6AB50C326EA4', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77')
GO
INSERT [dbo].[posts] ([post_id], [owner_user_id], [description], [commented_post_id], [original_post_id], [media_path], [post_type], [location_id], [created_date]) VALUES (N'8EB731DD-07DC-41DB-A576-6AB50C326EA4', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77', N'New description', N'00000000-0000-0000-0000-000000000000', N'00000000-0000-0000-0000-000000000000', N'C:\Users\Robert\Desktop\florin.jpg', 1, N'ChIJ-YqOoRUMSUcRoBLP7U19Ncw', CAST(N'2024-04-10T14:32:59.267' AS DateTime))
INSERT [dbo].[posts] ([post_id], [owner_user_id], [description], [commented_post_id], [original_post_id], [media_path], [post_type], [location_id], [created_date]) VALUES (N'8F8A147A-5B80-47E9-A092-A675F439A515', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77', N'final test', N'00000000-0000-0000-0000-000000000000', N'00000000-0000-0000-0000-000000000000', N'C:\Users\Robert\Desktop\florin.jpg', 1, N'ChIJ-YqOoRUMSUcRoBLP7U19Ncw', CAST(N'2024-04-10T05:51:37.920' AS DateTime))
INSERT [dbo].[posts] ([post_id], [owner_user_id], [description], [commented_post_id], [original_post_id], [media_path], [post_type], [location_id], [created_date]) VALUES (N'8FA829B1-FE71-4D13-8EEA-776DBAC4BD7E', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77', N'test ala bala', N'00000000-0000-0000-0000-000000000000', N'00000000-0000-0000-0000-000000000000', N'C:\Users\Robert\Desktop\florin.jpg', 1, N'ChIJabREaM0NSUcRhD2INUrVLPY', CAST(N'2024-04-10T04:10:22.053' AS DateTime))
INSERT [dbo].[posts] ([post_id], [owner_user_id], [description], [commented_post_id], [original_post_id], [media_path], [post_type], [location_id], [created_date]) VALUES (N'BDF1733F-615C-40CA-9D40-2E65369B911F', N'D5711B72-7E1F-4A8D-9226-38F6DA717A77', N'lorem ipsum', N'00000000-0000-0000-0000-000000000000', N'00000000-0000-0000-0000-000000000000', N'C:\Users\Robert\Desktop\florin.jpg', 1, N'+                          ', CAST(N'2024-04-08T23:15:54.773' AS DateTime))
INSERT [dbo].[posts] ([post_id], [owner_user_id], [description], [commented_post_id], [original_post_id], [media_path], [post_type], [location_id], [created_date]) VALUES (N'F4E08545-F179-4AD6-BB5D-C7F802EE6814', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77', N'test mentions', N'00000000-0000-0000-0000-000000000000', N'00000000-0000-0000-0000-000000000000', N'C:\Users\Robert\Desktop\florin.jpg', 1, N'ChIJsRIA_y9pSUcRuAQoqe_6ZEY', CAST(N'2024-04-10T04:38:16.067' AS DateTime))
GO
INSERT [dbo].[reactions] ([post_id], [user_id], [reaction]) VALUES (N'BDF1733F-615C-40CA-9D40-2E65369B911F', N'D5711B72-7E1F-4A8D-9226-38F6DA717A77', 0)
INSERT [dbo].[reactions] ([post_id], [user_id], [reaction]) VALUES (N'45A83770-98AA-4631-88BF-E782CDFA3A00', N'D5711B72-7E1F-4A8D-9226-38F6DA717A77', 0)
INSERT [dbo].[reactions] ([post_id], [user_id], [reaction]) VALUES (N'8FA829B1-FE71-4D13-8EEA-776DBAC4BD7E', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77', 0)
INSERT [dbo].[reactions] ([post_id], [user_id], [reaction]) VALUES (N'8F8A147A-5B80-47E9-A092-A675F439A515', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77', 0)
INSERT [dbo].[reactions] ([post_id], [user_id], [reaction]) VALUES (N'8EB731DD-07DC-41DB-A576-6AB50C326EA4', N'D6666B72-7E1F-4A8D-9226-38F6DA717A77', 0)
GO
INSERT [dbo].[users] ([user_id], [username], [profile_pic_path]) VALUES (N'D5711B72-7E1F-4A8D-9226-38F6DA717A77', N'fedus', N'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQe_EjnLAR6yWtIzoj01tVfrH2Va5Ld-GS7eIGHuGc9VQ&s')
INSERT [dbo].[users] ([user_id], [username], [profile_pic_path]) VALUES (N'D6666B72-7E1F-4A8D-9226-38F6DA717A77', N'florin', N'https://static4.libertatea.ro/wp-content/uploads/2023/09/florin-salam-la-40-de-intrebari-cu-denise-rifaikanal-d-1-scaled-e1695626612572.jpg')
GO
ALTER TABLE [dbo].[mentions]  WITH CHECK ADD  CONSTRAINT [FK_mentions_posts] FOREIGN KEY([post_id])
REFERENCES [dbo].[posts] ([post_id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[mentions] CHECK CONSTRAINT [FK_mentions_posts]
GO
ALTER TABLE [dbo].[mentions]  WITH CHECK ADD  CONSTRAINT [FK_mentions_users] FOREIGN KEY([user_id])
REFERENCES [dbo].[users] ([user_id])
GO
ALTER TABLE [dbo].[mentions] CHECK CONSTRAINT [FK_mentions_users]
GO
ALTER TABLE [dbo].[post_archive]  WITH CHECK ADD  CONSTRAINT [FK_post_archive_post_archive] FOREIGN KEY([post_id])
REFERENCES [dbo].[posts] ([post_id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[post_archive] CHECK CONSTRAINT [FK_post_archive_post_archive]
GO
ALTER TABLE [dbo].[post_hashtags]  WITH CHECK ADD  CONSTRAINT [FK_post_hashtags_hashtags] FOREIGN KEY([hashtag_id])
REFERENCES [dbo].[hashtags] ([hashtag_id])
GO
ALTER TABLE [dbo].[post_hashtags] CHECK CONSTRAINT [FK_post_hashtags_hashtags]
GO
ALTER TABLE [dbo].[post_hashtags]  WITH CHECK ADD  CONSTRAINT [FK_post_hashtags_posts] FOREIGN KEY([post_id])
REFERENCES [dbo].[posts] ([post_id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[post_hashtags] CHECK CONSTRAINT [FK_post_hashtags_posts]
GO
ALTER TABLE [dbo].[post_reports]  WITH CHECK ADD  CONSTRAINT [FK_post_reports_post_reports] FOREIGN KEY([post_id])
REFERENCES [dbo].[posts] ([post_id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[post_reports] CHECK CONSTRAINT [FK_post_reports_post_reports]
GO
ALTER TABLE [dbo].[post_saves]  WITH CHECK ADD  CONSTRAINT [FK_post_saves_posts] FOREIGN KEY([post_id])
REFERENCES [dbo].[posts] ([post_id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[post_saves] CHECK CONSTRAINT [FK_post_saves_posts]
GO
ALTER TABLE [dbo].[post_saves]  WITH CHECK ADD  CONSTRAINT [FK_post_saves_users] FOREIGN KEY([user_id])
REFERENCES [dbo].[users] ([user_id])
GO
ALTER TABLE [dbo].[post_saves] CHECK CONSTRAINT [FK_post_saves_users]
GO
ALTER TABLE [dbo].[posts]  WITH CHECK ADD  CONSTRAINT [FK_posts_posts] FOREIGN KEY([post_id])
REFERENCES [dbo].[posts] ([post_id])
GO
ALTER TABLE [dbo].[posts] CHECK CONSTRAINT [FK_posts_posts]
GO
ALTER TABLE [dbo].[posts]  WITH CHECK ADD  CONSTRAINT [FK_posts_users] FOREIGN KEY([owner_user_id])
REFERENCES [dbo].[users] ([user_id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[posts] CHECK CONSTRAINT [FK_posts_users]
GO
USE [master]
GO
ALTER DATABASE [blank-feed] SET  READ_WRITE 
GO