#The recommended releases of the several Apache Portable Runtime libraries are
# 
# APR 1.5.2, released April 29, 2015
# APR-util 1.5.4, released September 22, 2014
# APR-iconv 1.2.1, released November 26, 2007

set -e

# go somwhere safe
cd /tmp

# get the source to base APR 1.4.6
curl -L -O http://archive.apache.org/dist/apr/apr-1.5.2.tar.gz

# extractr it and to into the source
tar -xzvf apr-1.5.2.tar.gz
cd apr-1.5.2

# configure, make, make install
./configure
make
sudo make install

#reset and cleanup
cd /tmp
rm -rf apr-1.5.2.tar.gz apr-1.5.2

#do the same with apr-util
curl -L -O http://archive.apache.org/dist/apr/apr-util-1.5.4.tar.gz

#extract
tar -xzvf apr-util-1.5.4.tar.gz

cd apr-util-1.5.4

#cofigure, make, make install
./configure --with-apr=/usr/local/apr
#you need that extra parameter to configure...

make
sudo make install

#cleanup
cd /tmp
rm -rf apr-util-1.5.4* apr-1.5.2*

