echo "git add ."
git add .
echo "Input commit message: "
read msg
echo "git commit -m \"$msg\""
git commit -m msg
echo "git push origin master"
git push origin master