@ECHO OFF
set PATH=C:\nginx-1.9.7\
set IP=127.0.0.1:9000
start /D%PATH% nginx.exe
start /D%PATH% RunHiddenConsole.exe /D%PATH% php\php-cgi.exe -b /D%IP% -c /D%PATH% php\php.ini