# a=`ls *.proto`
# echo $a
probin=/usr/bin/protoc
for aa in `ls *.proto`;do
	echo ${aa}
	${probin} --cpp_out=./ ${aa}
done
for bb in `ls *.protoc`;do
	echo ${bb}
	${probin} --cpp_out=./  ${bb}
done

