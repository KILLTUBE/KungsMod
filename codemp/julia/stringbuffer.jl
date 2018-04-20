

# was in utils.jl
# gnah, seems like i cant pass array by reference...
function pastestring(buffer::Array{UInt8}, str::String)
	n = length(str)
	for i = 1 : n
		buffer[i] = str[i]
		#log("add $(str[i]) to $i\n")
	end
	buffer[n + 1] = UInt8(0)
	return buffer
end

type StringBuffer
	dirty::Bool
	cached::String
	buffer::Array{UInt8}
	StringBuffer(buffersize) = new(false, "", zeros(UInt8, buffersize))
	function StringBuffer(buffersize, startstring)
		this = new(false, startstring, zeros(UInt8, buffersize))
		setstring(this, startstring)
		return this
	end
end

pointer(this::StringBuffer) = pointer(this.buffer)

function setstring(this::StringBuffer, str::String)
	this.buffer = pastestring(this.buffer, str)
	this.dirty = true
end

function tostring(this::StringBuffer)
	if this.dirty
		this.cached = converttostring(this.buffer)
	end
	return this.cached
end

Base.size(this::StringBuffer) = size(this.buffer)
Base.length(this::StringBuffer) = length(this.buffer)

getbuffer(this::StringBuffer) = this.buffer

if false
	strbuf = StringBuffer(64)
	setstring(strbuf, "haiasd")
	tostring(strbuf)
	size(strbuf)

	strbuf2 = StringBuffer(32, "test")
	#strbuf2
	size(strbuf2)

end