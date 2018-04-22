type Explorer
	files::Vector{String}
	filter::StringBuffer
	newfilename::StringBuffer
	folder::Vector{String}
	function Explorer(foldername::AbstractString)
		return new(
			readdir(foldername),
			StringBuffer(256, ""),
			StringBuffer(256, "epic.jl"),
			#["."]
			["C:\\OpenSciTech\\codemp"]
		)
	end
end

function imgui(this::Explorer)

	i = 1
	for fold in this.folder
		if Button(fold)
			resize!(this.folder, i)
			this.files = readdir(join(this.folder, "/"))
			
			imgui_log("got: " * string(i) * "\n")
		end
		i += 1
		SameLine()
	end
	imgui_new_line()

	if Button("Clear Filter")
		setstring(this.filter, "")
	end
	InputText("filter", this.filter)

	if Button("New File")
		newfilename = join(this.folder, "/") * "/" * String(this.newfilename)
		log(console, "Create File", newfilename)
		file_put_contents(newfilename, "")
		update(this)
	end
	#PushID( pointer(this.filter) )
	InputText("new filename", this.newfilename)
	#PopID()

	filterstring = String(this.filter)
	for file in this.files
		if contains(file, filterstring) == false
			continue;
		end
		if Button(file)
			oldpathstring = join(this.folder, "/")
			if isdir(joinpath(oldpathstring, file))
				push!(this.folder, file)
				update(this)
			else
				fullfilename = joinpath(join(this.folder, "/"), file)
				log(console, "open", fullfilename)
				dock(TextEditor(fullfilename))
			end
		end
	end

end

function update(this::Explorer)
	this.files = readdir(join(this.folder, "/"))
end

if false
	explorer = Explorer(".")
	dock(explorer)
end
