cd ..\V5Render
prosv5 make template
cp V5render@1.0.0.zip ../v5Craft
cd ../v5Craft
prosv5 conduct fetch V5render@1.0.0.zip
prosv5 conduct uninstall V5render
prosv5 conduct apply V5render