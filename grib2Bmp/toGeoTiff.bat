REM N = 54.995000
REM W = -129.995
REM E = -60.005002
REM S = 20.005001

ECHO OFF
CALL "C:/OSGeo4W64/bin/o4w_env.bat"
ECHO ON

DEL composite.tif
DEL compositew.tif

gdal_translate -of GTiff -expand rgba composite.bmp composite.tif

gdalwarp -t_srs EPSG:4326 -to SRC_METHOD=NO_GEOTRANSFORM -r near -srcnodata "0 0 0 0" composite.tif compositew.tif

REM gdal2tiles -z 4 -w google -r average -s EPSG:4326 -g AIzaSyCnoazHa0WEibhtQZmBqlMtXcr9LOjN5Dw compositew.tif "public_html\charts\weather"

PAUSE