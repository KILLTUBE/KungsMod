function file_get_contents(filename)
	f = open(filename, "r")
	content = read(f)
	close(f)
	return String(content)
end

function file_put_contents(filename::AbstractString, contents)::Int
	f = open(filename, "w")
	bytes = write(f, contents)
	close(f)
	bytes
end