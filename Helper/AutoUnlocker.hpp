#pragma once

template<typename CS>
class AutoUnlocker {
public :
	AutoUnlocker(CS& cs) : cs_(cs) {
		cs_.lock();
	}
	~AutoUnlocker() {
		cs_.unlock();
	}
private :
	AutoUnlocker(){}
	AutoUnlocker(const AutoUnlocker& o) {}
	AutoUnlocker& operator=(const AutoUnlocker& o) { return *this; }
private :
	CS& cs_;
};

template<>
class AutoUnlocker<CRITICAL_SECTION> {
public :
	AutoUnlocker(CRITICAL_SECTION& cs) : cs_(cs) {
		::EnterCriticalSection(&cs_);
	}
	~AutoUnlocker() {
		::LeaveCriticalSection(&cs_);
	}
private :
	CRITICAL_SECTION& cs_;
};