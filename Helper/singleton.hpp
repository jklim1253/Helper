// Singleton Pattern
// - global access single unique object.
#pragma once

template<typename Cls>
class singleton {
protected :
	singleton(){}
	virtual ~singleton(){}
public :
	static Cls& Reference() {
		static Cls instance;
		return instance;
	}
};