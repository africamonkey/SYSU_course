wget http://cconline.sysu.edu.cn/html/JudgeOnline/web/log -O ../../../input/tmp
./fix_format < ../../../input/tmp > ../../../input/access_log
wget http://cconline.sysu.edu.cn/html/JudgeOnline/web/log1 -O ../../../input/tmp
./fix_format < ../../../input/tmp > ../../../input/access_log.1
rm ../../../input/tmp
rm -rf ../../../output/
