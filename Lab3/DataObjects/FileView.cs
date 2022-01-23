using System.Drawing;

namespace Lab3.DataObjects
{
    public class FileView
    {
        public Icon? FileIcon { get; set; }
        
        public string FilePath { get; set; }
        
        public string FileName { get; set; }

        public FileView()
        {
        }

        public FileView(string fileName, string filePath, Icon? fileIcon)
        {
            FileName = fileName;
            FilePath = filePath;
            FileIcon = fileIcon;
        }
    }
}