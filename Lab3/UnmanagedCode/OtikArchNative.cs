using System.Runtime.InteropServices;
using System.Text;

namespace Lab3.UnmanagedCode
{
    public static class OtikArchNative
    {
        private const string DllFilePath = "otik_dll.dll";

        [DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool MakeArch(StringBuilder newArchName,
            int newArchNameLen,
            StringBuilder inPath,
            int inPathLen,
            StringBuilder outPath,
            int outPathLen,
            bool useCompression,
            bool useArithmeticCompression,
            bool useContextCompression);
    }
}