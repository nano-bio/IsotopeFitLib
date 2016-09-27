using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace HDF5Test1
{
    public class Program
    {
        [DllImport("user32.dll")]
        public static extern int MessageBox(IntPtr hWnd, String text, String caption, int options);

        public static void Main(string[] args)
        {
            MessageBox(new IntPtr(), "dfoghsd", "asdfasd", 1);
        }
    }
}
