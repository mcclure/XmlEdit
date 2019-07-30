# Build icon files from PNG
# Only works on a macintosh with imagemagick installed (use brew)

all: windows.ico mac.icns

mac.icns: XmlEdit.png
	# Technique from https://stackoverflow.com/a/20703594
	# Assume XmlEdit.png is 1024x1024
	mkdir XmlEdit.iconset
	sips -z 16 16     XmlEdit.png --out XmlEdit.iconset/icon_16x16.png
	sips -z 32 32     XmlEdit.png --out XmlEdit.iconset/icon_16x16@2x.png
	sips -z 32 32     XmlEdit.png --out XmlEdit.iconset/icon_32x32.png
	sips -z 64 64     XmlEdit.png --out XmlEdit.iconset/icon_32x32@2x.png
	sips -z 128 128   XmlEdit.png --out XmlEdit.iconset/icon_128x128.png
	sips -z 256 256   XmlEdit.png --out XmlEdit.iconset/icon_128x128@2x.png
	sips -z 256 256   XmlEdit.png --out XmlEdit.iconset/icon_256x256.png
	sips -z 512 512   XmlEdit.png --out XmlEdit.iconset/icon_256x256@2x.png
	sips -z 512 512   XmlEdit.png --out XmlEdit.iconset/icon_512x512.png
	cp XmlEdit.png XmlEdit.iconset/icon_512x512@2x.png
	iconutil -c icns XmlEdit.iconset -o mac.icns

windows.ico: XmlEdit.png
	# Technique from https://doc.qt.io/qt-5/qtwidgets-widgets-icons-example.html
	# convert icon-16.png icon-32.png icon-256.png icon.ico

clean:
	rm -rf XmlEdit.iconset