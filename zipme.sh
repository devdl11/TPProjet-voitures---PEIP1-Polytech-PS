if [ ! -d "./release" ]
then
  mkdir "release"
fi

tar --exclude="./release" --exclude="./cmake-*" --exclude="./.*" --exclude="./mainDir" -czf "release/$(date +%s).tar" "."