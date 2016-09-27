using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HDF5DotNet;

namespace nugetCreateTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(H5F.is_hdf5(@".\testfile.h5"));
            Console.ReadLine();
        }
    }
}
