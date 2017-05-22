read -p "What did you update: " update

git add *
git commit -m "$update"
git push -u origin master

