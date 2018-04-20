using SQLite
using DataFrames

if ! isdefined(:db)
	db = SQLite.DB("gui.db")
end

function DeleteAndRecreateDocksTable()
	SQLite.query(db, """
		drop table if exists docks
	""")
	SQLite.query(db, """
		create table docks (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			`index` INTEGER,
			label text,
			pos_x  INTEGER,
			pos_y  INTEGER,
			size_x INTEGER,
			size_y INTEGER,
			status INTEGER,
			active text,
			opened text,
			location text,
			child_a INTEGER,
			child_b INTEGER,
			tab_prev INTEGER,
			tab_next INTEGER,
			parent INTEGER
		)
	""")
end

#DeleteAndRecreateDocksTable()


function AddDockToDatabase(tmp)
	label = tmp["label"]

	# delete any docks with same label, there should be either 0 or 1...
	SQLite.query(db, "DELETE FROM docks WHERE label = '$label'")

	# and just insert new dock into table
	query = """
		INSERT INTO docks
		(
			`index`, label, pos_x, pos_y, size_x, size_y, status, active, opened, location,
			child_a, child_b, tab_prev, tab_next, parent
		)
		VALUES (
			$(tmp["index"]),
			'$(tmp["label"])',
			$(tmp["x"]),
			$(tmp["y"]),
			$(tmp["size_x"]),
			$(tmp["size_y"]),
			$(tmp["status"]),
			$(tmp["active"]),
			$(tmp["opened"]),
			'$(tmp["location"])',
			$(tmp["child0"]),
			$(tmp["child1"]),
			$(tmp["prev_tab"]),
			$(tmp["next_tab"]),
			$(tmp["parent"])
		)

	"""
	SQLite.query(db, query)
end

function SaveDocksToDatabase()
	n = DockCount()
	for i = 0 : n - 1
		d = DockByID(i)
		AddDockToDatabase(d)
	end
end

function GetDockInfoByLabel(label)
	result = SQLite.query(db, "SELECT * FROM docks WHERE label = '$label' LIMIT 1")
	if size(result)[1] == 0
		return nothing
	end
	DataFrameRow(result, 1)
end

