
#install cmake 3.18
wget https://github.com/Kitware/CMake/releases/download/v3.18.2/cmake-3.18.2.tar.gz
tar xf cmake-3.18.2.tar.gz
cd cmake-3.18.2
./bootstrap && make && sudo make install
cd ..
#install gcc-10.2
sudo apt update
sudo apt upgrade
sudo apt install build-essential wget m4 flex bison
wget https://ftpmirror.gnu.org/gcc/gcc-10.2.0/gcc-10.2.0.tar.xz
tar xf gcc-10.2.0.tar.xz
cd gcc-10.2.0
contrib/download_prerequisites
cd ~
mkdir build && cd build
../gcc-10.1.0/configure -v --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=/usr/local/gcc-10.2.0 --enable-checking=release --enable-languages=c,c++,fortran --disable-multilib --program-suffix=-10.2
## make soft link
sudo ln -sf /usr/local/gcc-10.2.0/bin/gcc-10.2 /usr/bin/gcc
sudo ln -sf /usr/local/gcc-10.2.0/bin/gcc-10.2 /usr/local/bin/gcc
sudo ln -sf /usr/local/gcc-10.2.0/bin/g++-10.2 /usr/bin/g++
sudo ln -sf /usr/local/gcc-10.2.0/bin/g++-10.2 /usr/local/bin/g++
sudo ln -sf /usr/local/gcc-10.2.0/bin/c++-10.2 /usr/bin/c++
sudo ln -sf /usr/local/gcc-10.2.0/bin/c++-10.2 /usr/local/bin/c++
# qt can get correct cpp path from /usr/local/bin/cpp
sudo ln -sf /usr/local/gcc-10.2.0/bin/cpp-10.2 /usr/bin/cpp
sudo ln -sf /usr/local/gcc-10.2.0/bin/cpp-10.2 /usr/local/bin/cpp

#install boost-1.74.0
wget https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz
tar xf boost_1_74_0.tar.gz
cd boost_1_74_0
./bootstrap.sh
sudo ./b2 install
echo "done"
