using System.Runtime.InteropServices;
using System.Text;

namespace Lab3.UnmanagedCode
{
    public static class OtikArchNative
    {
        private const string DllFilePath = @"\..\..\..\..\..\x64\Release\otik_dll.dll";

        [DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool MakeArch(StringBuilder new_arch_name,
            int new_arch_name_len,
            StringBuilder in_path,
            int in_path_len,
            StringBuilder out_path,
            int out_pathLen,
            bool use_context_independent_compression,
            bool use_context_compression);
    }
}