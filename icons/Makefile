# Build icon files from PNG. Rerun this when PNG changes
# Only works on a macintosh with imagemagick installed (use brew)

all: windows.ico mac.icns

mac.icns: XmlEdit.iconset/sentinel
	iconutil -c icns XmlEdit.iconset -o mac.icns

windows.ico: XmlEdit.iconset/sentinel
	# Technique from https://doc.qt.io/qt-5/qtwidgets-widgets-icons-example.html
	convert XmlEdit.iconset/icon_16x16.png XmlEdit.iconset/icon_32x32.png \
	        XmlEdit.iconset/icon_256x256.png windows.ico

XmlEdit.iconset/sentinel: XmlEdit.png XmlEdit_16_retina.png
	# Technique from https://stackoverflow.com/a/20703594
	# Assume XmlEdit.png is 1024x1024
	mkdir -p XmlEdit.iconset

	# Source images from XmlEdit.png
	sips -z 32 32     XmlEdit.png --out XmlEdit.iconset/icon_32x32.png
	sips -z 64 64     XmlEdit.png --out XmlEdit.iconset/icon_32x32@2x.png
	sips -z 128 128   XmlEdit.png --out XmlEdit.iconset/icon_128x128.png
	sips -z 256 256   XmlEdit.png --out XmlEdit.iconset/icon_128x128@2x.png
	sips -z 256 256   XmlEdit.png --out XmlEdit.iconset/icon_256x256.png
	sips -z 512 512   XmlEdit.png --out XmlEdit.iconset/icon_256x256@2x.png
	sips -z 512 512   XmlEdit.png --out XmlEdit.iconset/icon_512x512.png
	cp XmlEdit.png XmlEdit.iconset/icon_512x512@2x.png

	# The 1024x1024 icon is too blurry at 16x16, so do these two from a separate base
	sips -z 16 16     XmlEdit_16_retina.png --out XmlEdit.iconset/icon_16x16.png
	cp XmlEdit_16_retina.png XmlEdit.iconset/icon_16x16@2x.png

	touch XmlEdit.iconset/sentinel

clean:
	rm -rf XmlEdit.iconset
