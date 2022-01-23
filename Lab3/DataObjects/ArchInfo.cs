using System.Collections.Generic;
using System.Text;

namespace Lab3.DataObjects
{
    public class ArchInfo
    {
        public StringBuilder ArchName { get; set; }
        public StringBuilder FilePaths { get; set; }
        public StringBuilder OutFilaPath { get; set; }

        public ArchInfo(string archName, List<string> filePaths, string outPath)
        {
            if (!string.IsNullOrEmpty(archName))
            {
                ArchName = new StringBuilder(archName);
            }

            if (!string.IsNullOrEmpty(outPath))
            {
                OutFilaPath = new StringBuilder(outPath);
            }

            if (filePaths.Count > 0)
            {
                FilePaths = new StringBuilder();
                foreach (var filePath in filePaths)
                {
                    FilePaths.Append($"\"{filePath}\"");
                }
            }
        }

        public ArchInfo()
        {
        }
    }
}