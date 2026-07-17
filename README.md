# 🎵 MP3 Tag Reader & Editor in C

A command-line based **MP3 Tag Reader and Editor** developed in **C** that allows users to read and modify **ID3v2 metadata tags** in MP3 files. The application extracts information such as the song title, artist, album, genre, and year, and enables users to update these fields without affecting the audio content.

---

## 📌 Features

- View MP3 metadata (ID3v2 tags)
- Edit MP3 tag information
- Supports the following tags:
  - Title
  - Artist
  - Album
  - Genre
  - Year
  - Comment
- Preserves the original audio data
- User-friendly command-line interface
- Handles invalid or unsupported MP3 files

---

## 🛠️ Technologies Used

- C Programming
- File Handling
- Binary File Processing
- ID3v2 Tag Parsing
- Command Line Arguments
- GCC Compiler
- Linux

---

## 🔍 How It Works

### View Mode

1. Open the MP3 file.
2. Verify the ID3v2 header.
3. Read each metadata frame.
4. Display tag information such as:
   - Title
   - Artist
   - Album
   - Year
   - Genre
   - Comment

### Edit Mode

1. Open the MP3 file.
2. Locate the selected ID3v2 frame.
3. Replace the existing metadata with the new value.
4. Save the updated MP3 file while preserving the audio data.

---

## 📖 Command Usage

### View MP3 Tags

```bash
./mp3_tag_reader -v sample.mp3
```

### Edit MP3 Tags

```bash
./mp3_tag_reader -e -t "New Song Title" sample.mp3
```

Example options:

```text
-t  Title
-a  Artist
-A  Album
-y  Year
-g  Genre
-c  Comment
```

---

## 🚀 Compilation

```bash
gcc *.c -o mp3_tag_reader
```

or

```bash
make
```

---

## ▶️ Example

### View

```bash
$ ./mp3_tag_reader -v sample.mp3

------------------------------
MP3 TAG INFORMATION
------------------------------
Title   : Shape of You
Artist  : Ed Sheeran
Album   : Divide
Year    : 2017
Genre   : Pop
Comment : Sample Song
```

### Edit

```bash
$ ./mp3_tag_reader -e -a "Imagine Dragons" sample.mp3

Artist Updated Successfully!
```

---

## 💡 ID3v2 Metadata Structure

```
+-----------------------+
| ID3 Header            |
+-----------------------+
| TIT2  (Title)         |
+-----------------------+
| TPE1  (Artist)        |
+-----------------------+
| TALB  (Album)         |
+-----------------------+
| TYER/TDRC (Year)      |
+-----------------------+
| TCON  (Genre)         |
+-----------------------+
| COMM  (Comment)       |
+-----------------------+
| Audio Data            |
+-----------------------+
```

---

## 📚 Concepts Covered

- File Handling
- Binary File Parsing
- ID3v2 Metadata Format
- Endianness Handling
- String Manipulation
- Command Line Arguments
- Modular Programming
- Memory Management

---

## 🎯 Learning Outcomes

Through this project, I gained practical experience in:

- Parsing binary file formats
- Reading and modifying ID3v2 metadata frames
- Working with file pointers and offsets
- Handling endian conversion
- Preserving binary file integrity during updates
- Developing modular command-line applications in C

---

## 🔒 Applications

- MP3 metadata management
- Music library organization
- Audio file information editing
- Learning binary file structures
- Multimedia software development

---

## 🔮 Future Enhancements

- Support for ID3v1 and ID3v2.4
- Display album artwork
- Batch editing of multiple MP3 files
- UTF-8 and Unicode tag support
- Interactive menu-driven interface
- Playlist management

---

## 👨‍💻 Author

**Muhammed Sabith**

Embedded Software Engineer

**Skills**
- C Programming
- Embedded C
- Linux
- File Handling
- Binary File Processing
- Data Structures
- Bit Manipulation

---

## 📜 License

This project is intended for educational and learning purposes.
