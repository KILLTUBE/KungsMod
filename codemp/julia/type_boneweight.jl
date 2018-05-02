uint_a = UInt32(0x806020e2)
uint_b = UInt32(0x00995c0a)

nicehex(uint32::UInt32) = "0x" * lpad(hex(uint32), 8, "0")
nicehex(uint16::UInt16) = "0x" * lpad(hex(uint16), 4, "0")

type BoneWeight
	numBones::UInt8
	
	# a bone weight has 10 bits, so UInt16 comes closest
	b0::UInt16
	b1::UInt16
	b2::UInt16
	b3::UInt16
	
	i0::UInt8
	i1::UInt8
	i2::UInt8
	i3::UInt8
		
	weight0::Float32
	weight1::Float32
	weight2::Float32
	weight3::Float32
	
	# uint_a format is:
	#  - bits  0 to  5: unknown but used, e.g. value 2
	#  - bits  5 to 10: boneIndex 0
	#  - bits 10 to 15: boneIndex 1
	#  - bits 15 to 20: boneIndex 2
	#  - bits 20 to 25: boneIndex 3
	#  - bits 25 
	
	function BoneWeight(uint_a::UInt32, uint_b::UInt32)
		boneWeight = new()
		boneWeight.numBones = UInt8(1) # at least 1 bone
		boneWeight.numBones += uint_a >> 30 # add the first 2 bits, amount of extra bones
		
		# set the lower eight bits for each bone weight from uint_b
		boneWeight.b0 = (uint_b >> 24) & 0xff
		boneWeight.b1 = (uint_b >> 16) & 0xff
		boneWeight.b2 = (uint_b >>  8) & 0xff
		boneWeight.b3 = (uint_b >>  0) & 0xff
		
		# and xor the higher 2 bits from uint_a, from bit [20...28]
		boneWeight.b0 |= ((uint_a >> 20) & 3) << 8
		boneWeight.b1 |= ((uint_a >> 22) & 3) << 8
		boneWeight.b2 |= ((uint_a >> 24) & 3) << 8
		boneWeight.b3 |= ((uint_a >> 26) & 3) << 8
		
		boneWeight.weight0 = boneWeight.b0 / 1023
		boneWeight.weight1 = boneWeight.b1 / 1023
		boneWeight.weight2 = boneWeight.b2 / 1023
		boneWeight.weight3 = boneWeight.b3 / 1023
		
		# read 5 bits each from uint_a, which make up the bone indices
		boneWeight.i0 |= (uint_a >>  0) & 0b11111
		boneWeight.i1 |= (uint_a >>  5) & 0b11111
		boneWeight.i2 |= (uint_a >> 10) & 0b11111
		boneWeight.i3 |= (uint_a >> 15) & 0b11111
		
		println("uint_a=", nicehex(uint_a))
		println("uint_b=", nicehex(uint_b))
		
		println("numBones=", boneWeight.numBones)
		println("i0=", boneWeight.i0, " b0=", nicehex(boneWeight.b0), " weight0=", boneWeight.weight0)
		println("i1=", boneWeight.i1, " b1=", nicehex(boneWeight.b1), " weight1=", boneWeight.weight1)
		println("i2=", boneWeight.i2, " b2=", nicehex(boneWeight.b2), " weight2=", boneWeight.weight2)
		println("i3=", boneWeight.i3, " b3=", nicehex(boneWeight.b3), " weight3=", boneWeight.weight3)

		uint_a = UInt32(0)
		uint_b = UInt32(0)

		boneWeight.b0 = UInt16(round( boneWeight.weight0 * 1023 ))
		boneWeight.b1 = UInt16(round( boneWeight.weight1 * 1023 ))
		boneWeight.b2 = UInt16(round( boneWeight.weight2 * 1023 ))
		boneWeight.b3 = UInt16(round( boneWeight.weight3 * 1023 ))
		
		# put the higher 8 bits back into uint_b
		uint_b |= UInt32(boneWeight.b0 & 0xff) << 24
		uint_b |= UInt32(boneWeight.b1 & 0xff) << 16
		uint_b |= UInt32(boneWeight.b2 & 0xff) <<  8
		uint_b |= UInt32(boneWeight.b3 & 0xff) <<  0
		
		# add the numBones back into uint_a
		uint_a |= UInt32(boneWeight.numBones - 1) << 30 # substract the minimal 1 bone

		# add the higher 2 bits into uint_a
		uint_a |= UInt32((boneWeight.b0 >> 8) & 0b11) << 20
		uint_a |= UInt32((boneWeight.b1 >> 8) & 0b11) << 22
		uint_a |= UInt32((boneWeight.b2 >> 8) & 0b11) << 24
		uint_a |= UInt32((boneWeight.b3 >> 8) & 0b11) << 26
		
		uint_a |= UInt32(boneWeight.i0) <<  0
		uint_a |= UInt32(boneWeight.i1) <<  5
		uint_a |= UInt32(boneWeight.i2) << 10
		uint_a |= UInt32(boneWeight.i3) << 15
		
		println("uint_a=", nicehex(uint_a))
		println("uint_b=", nicehex(uint_b))
		
		return boneWeight
	end
end


bw = BoneWeight(uint_a, uint_b)

b0 = bw.b0
b1 = bw.b1
b2 = bw.b2
b3 = bw.b3
weight0 = bw.weight0
weight1 = bw.weight1
weight2 = bw.weight2
weight3 = bw.weight3
print("b0=$b0 b1=$b1 b2=$b2 b3=$b3 weight0=$weight0 weight1=$weight1 weight2=$weight2 weight3=$weight3")