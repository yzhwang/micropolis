python tools/flextGL/flextGLgen.py --template=glfw --outdir=generated src/extensions.glprofile
python tools/configGen/configGen.py -Hh -Ccpp -Dgenerated src/config.xml
python tools/formatMapGen.py -Hh -Ccpp -Dgenerated
