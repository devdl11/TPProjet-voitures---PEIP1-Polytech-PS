if [ ! -d "./release" ]
then
  mkdir "release"
fi

tar --exclude="./release" --exclude="./cmake-*" --exclude="./.*" -czf "release/$(date +%s).tar" "."