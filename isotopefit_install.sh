apt-get install wget gcc make g++ libc6-dev p7zip
mkdir dependencies
cd dependencies
wget ftp://ftp.hdfgroup.org/lib-external/szip/2.1/src/szip-2.1.tar.gz
tar xfvz szip-2.1.tar.gz
cd szip-2.1
./configure --prefix=/usr/local
make
make install
cd ..
wget http://zlib.net/zlib-1.2.8.tar.gz
tar xfvz zlib-1.2.8.tar.gz
cd zlib-1.2.8
./configure
make
make install prefix=/usr/local
cd ..
wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.10/hdf5-1.10.0/src/hdf5-1.10.0.tar.gz
tar xfvz hdf5-1.10.0.tar.gz
cd hdf5-1.10.0
./configure --prefix=/usr/local --enable-cxx --with-zlib=/usr/local/include,/usr/local/lib --with-szlib=/usr/local
make
make install
cd ..
wget ftp://ftp.gnu.org/gnu/gsl/gsl-2.2.1.tar.gz
tar xfvz gsl-2.2.1.tar.gz
cd gsl-2.2.1
./configure
make
make install
cd ..
https://sourceforge.net/projects/matio/files/latest/download
mv download download.7z
p7zip -d download.7z
chmod a+x matio-1.5.9 -R
cd matio-1.5.9
./configure --with-zlib=/usr/local --with-default-file-ver=5
make
make install
cd ../..
