for /R %%F IN (*) DO (
	pushd %%~dpF
	attrib -R %%~nF%%~xF
	popd
)


pause