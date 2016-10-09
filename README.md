# Helper
Helper, c++, mfc

# INIHelper
ini file helper class.

public method.

	useFile(path)
	useSection(section)
	SetValue(key, value)
	SetValue(section, key, value)
	SetValue(path, section, key, value)
	GetValue(key, default_value)
	GetValue(section, key, default_value)
	GetValue(path, section, key, default_value)
	GetValue<value_type>(key)
	GetValue<value_type>(section, key)
	GetValue<value_type>(path, section, key)

# TimeHelper
time helper class.

public method.

	now()
	time(SYSTEMTIME)

# ThreadHelper
thread helper class.

public method.

	run()
	run(Instruction*)
	stop(exitcode)
	wait(millisecond)

# LogHelper
log helper class.

public method.

	setLogFile(path)
	addMessage(msg)
	operator(msg)

# DLLHelper
under implementation.
