#!/bin/sh
cp -f ../../../libs/fmodex/lib/osx/libfmodex.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/libfmodex.dylib"; install_name_tool -change ./libfmodex.dylib @executable_path/libfmodex.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME";
rm -R -f "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources/data"; mkdir -p  "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources/"; cp -f -R bin/data "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources/";
