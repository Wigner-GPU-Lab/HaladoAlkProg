#include "Vector.h"
#include <iostream>

int main()
{
	auto err = [](auto str){ std::cout << "Vector.h error in: " << str << "\n"; std::exit(-1); };

	//Test default constructor:
	{
		Vector<double> u;
		if(u.size() != 0)         { err("default contructor test [size]");           }
		if(u.begin() != u.end())  { err("default contructor test [begin == end]");   }
		if(u.cbegin() != u.cend()){ err("default contructor test [cbegin == cend]"); }
	}

	//Test list initialization and indexing:
	{
		Vector<double> a = {3.1, 5.2, 9.3};
		if(a.size() != 3)                            { err("initializer list constructor test [size]");               }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3){ err("initializer list constructor test [indexing with []]");   }
		if(a(0) != 3.1 || a(1) != 5.2 || a(2) != 9.3){ err("initializer list constructor test [indexing with ()]");   }
		if( ++ ++ ++(a.begin()) != a.end() )         { err("initializer list constructor test [begin + 3 == end]");   }
		if( ++ ++ ++(a.cbegin()) != a.cend() )       { err("initializer list constructor test [cbegin + 3 == cend]"); }
	}

	//Test copy constructor:
	{
		Vector<double> a = {3.1, 5.2, 9.3};
		Vector<double> b{a};
		if(b.size() != 3)                            { err("copy constructor test [size]");               }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3){ err("copy constructor test [elements]");           }
		if( ++ ++ ++(b.begin()) != b.end() )         { err("copy constructor test [begin + 3 == end]");   }
		if( ++ ++ ++(b.cbegin()) != b.cend() )       { err("copy constructor test [cbegin + 3 == cend]"); }
		if(a.size() != 3)                            { err("copy constructor test [src size]");           }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3){ err("copy constructor test [src elements]");       }
	}

	//Test move constructor:
	{
		Vector<double> a = {3.1, 5.2, 9.3};
		Vector<double> b{ std::move(a) };
		if(a.size() != 0)                            { err("move constructor test [src size]");             }
		if(a.begin() != a.end())                     { err("move constructor test [src begin == src end]"); }
		if(b.size() != 3)                            { err("move constructor test [size]");                 }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3){ err("move constructor test [elements]");             }
		if( ++ ++ ++(b.begin()) != b.end() )         { err("move constructor test [begin + 3 == end]");     }
		if( ++ ++ ++(b.cbegin()) != b.cend() )       { err("move constructor test [cbegin + 3 == cend]");   }
	}
	
	//Test indexible function constructor:
	{
		Vector<int> a{ [](int i){ return 100*i*i+20*i+5; }, 4};
		if(a.size() != 4)                                         { err("constructor from indexible test [size]");     }
		if(a[0] != 5 || a[1] != 125 || a[2] != 445 || a[3] != 965){ err("constructor from indexible test [elements]"); }
	}

	//Test assignment:
	{
		Vector<double> a = {3.1, 5.2, 9.3};
		Vector<double> b;
		b = a;
		if(b.size() != 3)                            { err("assignment test [size]");         }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3){ err("assignment test [elements]");     }
		if(a.size() != 3)                            { err("assignment test [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3){ err("assignment test [src elements]"); }
	}

	//Test self assignment:
	{
		Vector<double> c = {3.1, 5.2, 9.3};
		c = c;
		if(c.size() != 3)                            { err("self assignment test [size]");     }
		if(c[0] != 3.1 || c[1] != 5.2 || c[2] != 9.3){ err("self assignment test [elements]"); }
	}

	//Test move assignment:
	{
		Vector<double> a = {3.1, 5.2, 9.3};
		Vector<double> b;
		b = std::move(a);
		if(a.begin() != a.end())                     { err("assignment test [src begin == src end]"); }
		if(a.size() != 0)                            { err("assignment test [src size]");             }
		if(b.size() != 3)                            { err("assignment test [size]");                 }
		if(b[0] != 3.1 || b[1] != 5.2 || b[2] != 9.3){ err("assignment test [elements]");             }
	}

	//Test self move assignment:
	{
		Vector<double> c = {3.1, 5.2, 9.3};
		c = std::move(c);
		if(c.size() != 3)                            { err("self assignment test [size]");     }
		if(c[0] != 3.1 || c[1] != 5.2 || c[2] != 9.3){ err("self assignment test [elements]"); }
	}

	//Test length, sqlength:
	{
		Vector<double> c = {2.0, -3.0, 6.0};
		double l = length(c);
		double sql = sqlength(c);
		if(std::abs(l - 7.0) > 1e-15)                 { err("length test [value]");        }
		if(std::abs(sql - 49.0) > 1e-15)              { err("sq length test [value]");     }
		if(c.size() != 3)                             { err("length test [src size]");     }
		if(c[0] != 2.0 || c[1] != -3.0 || c[2] != 6.0){ err("length test [src elements]"); }
	}

	//Test operator- (l-value, l-value) (more detailed test, since later tests depend on it)
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {4.0, 10.0, 2.0};
		Vector<double> res = b - a;
		if(a.size() != 3)                              { err("operator- test (l-value, l-value) [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3)  { err("operator- test (l-value, l-value) [src elements]"); }
		if(b.size() != 3)                              { err("operator- test (l-value, l-value) [src size]");     }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("operator- test (l-value, l-value) [src elements]"); }
		if(res.size() != 3)                            { err("operator- test (l-value, l-value) [size]");         }
		if(std::abs(ref[0]-res[0]) > 1e-15 ||
		   std::abs(ref[1]-res[1]) > 1e-15 || 
		   std::abs(ref[2]-res[2]) > 1e-15    ){ err("operator- test (l-value, l-value) [elements]"); }
	}

	//Test operator- (r-value, l-value)
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {4.0, 10.0, 2.0};
		Vector<double> res = std::move(b) - a;
		if(a.size() != 3)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(b.size() != 0)                              { err("operator- test (r-value, l-value) [src size]");     }
		if(res.size() != 3)                            { err("operator- test (r-value, l-value) [size]");         }
		if(a[0] != 3.1 || a[1] !=  5.2 || a[2] !=  9.3){ err("operator- test (r-value, l-value) [src elements]"); }
		if(length(res - ref) > 1e-15)                  { err("operator- test (r-value, l-value) [value]");        }
	}

	//Test operator- (l-value, r-value)
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {4.0, 10.0, 2.0};
		Vector<double> res = b - std::move(a);
		if(a.size() != 0)                              { err("operator- test (l-value, r-value) [src size]");     }
		if(b.size() != 3)                              { err("operator- test (l-value, r-value) [src size]");     }
		if(res.size() != 3)                            { err("operator- test (l-value, r-value) [size]");         }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("operator- test (l-value, r-value) [src elements]"); }
		if(length(res - ref) > 1e-15)                  { err("operator- test (l-value, r-value) [value]");        }
	}

	//Test operator- (r-value, r-value)
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {4.0, 10.0, 2.0};
		Vector<double> res = std::move(b) - std::move(a);
		if(a.size() != 3)            { err("operator- test (r-value, r-value) [src size]"); }//this argument was not reused!
		if(b.size() != 0)            { err("operator- test (r-value, r-value) [src size]"); }
		if(res.size() != 3)          { err("operator- test (r-value, r-value) [size]");     }
		if(length(res - ref) > 1e-15){ err("operator- test (r-value, r-value) [value]");    }
	}

	//Test operator+ (l-value, l-value)
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {10.2, 20.4, 20.6};
		Vector<double> res = a + b;
		if(a.size() != 3)                              { err("operator+ test (l-value, l-value) [src size]");     }
		if(b.size() != 3)                              { err("operator+ test (l-value, l-value) [src size]");     }
		if(res.size() != 3)                            { err("operator+ test (l-value, l-value) [size]");         }
		if(a[0] != 3.1 || a[1] !=  5.2 || a[2] !=  9.3){ err("operator+ test (l-value, l-value) [src elements]"); }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("operator+ test (l-value, l-value) [src elements]"); }
		if(length(res - ref) > 1e-15)                  { err("operator+ test (l-value, l-value) [value]");        }
	}

	//Test operator+ (r-value, l-value)
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {10.2, 20.4, 20.6};
		Vector<double> res = std::move(a) + b;
		if(a.size() != 0)                              { err("operator+ test (r-value, l-value) [src size]");     }
		if(b.size() != 3)                              { err("operator+ test (r-value, l-value) [src size]");     }
		if(res.size() != 3)                            { err("operator+ test (r-value, l-value) [size]");         }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("operator+ test (r-value, l-value) [src elements]"); }
		if(length(res - ref) > 1e-15)                  { err("operator+ test (r-value, l-value) [value]");        }
	}

	//Test operator+ (l-value, r-value)
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {10.2, 20.4, 20.6};
		Vector<double> res = a + std::move(b);
		if(a.size() != 3)                              { err("operator+ test (l-value, r-value) [src size]");     }
		if(b.size() != 0)                              { err("operator+ test (l-value, r-value) [src size]");     }
		if(res.size() != 3)                            { err("operator+ test (l-value, r-value) [size]");         }
		if(a[0] != 3.1 || a[1] !=  5.2 || a[2] !=  9.3){ err("operator+ test (l-value, r-value) [src elements]"); }
		if(length(res - ref) > 1e-15)                  { err("operator+ test (l-value, r-value) [value]");        }
	}

	//Test operator+ (r-value, r-value)
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {10.2, 20.4, 20.6};
		Vector<double> res = std::move(a) + std::move(b);
		if(a.size() != 0)            { err("operator+ test (r-value, r-value) [src size]"); }
		if(b.size() != 3)            { err("operator+ test (r-value, r-value) [src size]"); }//this argument was not reused!
		if(res.size() != 3)          { err("operator+ test (r-value, r-value) [size]");     }
		if(length(res - ref) > 1e-15){ err("operator+ test (r-value, r-value) [value]");    }
	}

	//Test +=:
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {10.2, 20.4, 20.6};
	    a += b;
		if(a.size() != 3)                              { err("+= test [size]");         }
		if(b.size() != 3)                              { err("+= test [src size]");     }
		if(b[0] != 7.1 || b[1] != 15.2 || b[2] != 11.3){ err("+= test [src elements]"); }
		if(length(a - ref) > 1e-15)                    { err("+= test [value]");        }
		
	}

	//Test -=:
	{
		Vector<double> a   = {3.1, 5.2, 9.3};
		Vector<double> b   = {7.1, 15.2, 11.3};
		Vector<double> ref = {4.0, 10.0, 2.0};
		b -= a;
		if(a.size() != 3)                            { err("-= test [size]");         }
		if(b.size() != 3)                            { err("-= test [src size]");     }
		if(a[0] != 3.1 || a[1] != 5.2 || a[2] != 9.3){ err("-= test [src elements]"); }
		if(length(b - ref) > 1e-15)                  { err("-= test [value]");        }
	}

	//Test *=:
	{
		Vector<double> a   = {3.1, -5.2,  9.3};
		Vector<double> ref = {6.2, -10.4, 18.6};
		a *= 2.0;
		if(a.size() != 3)          { err("*= test [size]");  }
		if(length(a - ref) > 1e-15){ err("*= test [value]"); }
	}

	//Test operator* (l-value, scalar)
	{
		Vector<double> a   = {3.1, -5.2,  9.3};
		Vector<double> ref = {6.2, -10.4, 18.6};
		Vector<double> res = a * 2.0;
		if(a.size()   != 3)                           { err("operator* test (l-value, scalar) [src size]");     }
		if(res.size() != 3)                           { err("operator* test (l-value, scalar) [size]");         }
		if(a[0] != 3.1 || a[1] != -5.2 || a[2] != 9.3){ err("operator* test (l-value, scalar) [src elements]"); }
		if(length(res - ref) > 1e-15)                 { err("operator* test (l-value, scalar) [value]");        }
	}

	//Test operator* (r-value, scalar)
	{
		Vector<double> a   = {3.1, -5.2,  9.3};
		Vector<double> ref = {6.2, -10.4, 18.6};
		Vector<double> res = std::move(a) * 2.0;
		if(a.size()   != 0)          { err("operator* test (r-value, scalar) [src size]");     }
		if(res.size() != 3)          { err("operator* test (r-value, scalar) [size]");         }
		if(length(res - ref) > 1e-15){ err("operator* test (r-value, scalar) [value]");        }
	}

	//Test operator* (scalar, l-value)
	{
		Vector<double> a   = {3.1, -5.2,  9.3};
		Vector<double> ref = {6.2, -10.4, 18.6};
		Vector<double> res = 2.0 * a;
		if(a.size()   != 3)                           { err("operator* test (scalar, l-value) [src size]");     }
		if(res.size() != 3)                           { err("operator* test (scalar, l-value) [size]");         }
		if(a[0] != 3.1 || a[1] != -5.2 || a[2] != 9.3){ err("operator* test (scalar, l-value) [src elements]"); }
		if(length(res - ref) > 1e-15)                 { err("operator* test (scalar, l-value) [value]");        }
	}

	//Test operator* (scalar, r-value)
	{
		Vector<double> a   = {3.1, -5.2,  9.3};
		Vector<double> ref = {6.2, -10.4, 18.6};
		Vector<double> res = 2.0 * std::move(a);
		if(a.size()   != 0)          { err("operator* test (scalar, r-value) [src size]");     }
		if(res.size() != 3)          { err("operator* test (scalar, r-value) [size]");         }
		if(length(res - ref) > 1e-15){ err("operator* test (scalar, r-value) [value]");        }
	}

	//Test /=:
	{
		Vector<double> a   = {6.2, -10.4, 18.6};
		Vector<double> ref = {3.1, -5.2,  9.3};
		a /= 2.0;
		if(a.size() != 3)          { err("/= test [size]");  }
		if(length(a - ref) > 1e-15){ err("/= test [value]"); }
	}

	//Test operator/ (l-value, scalar)
	{
		Vector<double> a   = {6.2, -10.4, 18.6};
		Vector<double> ref = {3.1, -5.2,  9.3};
		Vector<double> res = a / 2.0;
		if(a.size()   != 3)                             { err("operator/ test (l-value, scalar) [src size]");     }
		if(res.size() != 3)                             { err("operator/ test (l-value, scalar) [size]");         }
		if(a[0] != 6.2 || a[1] != -10.4 || a[2] != 18.6){ err("operator/ test (l-value, scalar) [src elements]"); }
		if(length(res - ref) > 1e-15)                   { err("operator/ test (l-value, scalar) [value]");        }
	}

	//Test operator/ (r-value, scalar)
	{
		Vector<double> a   = {6.2, -10.4, 18.6};
		Vector<double> ref = {3.1, -5.2,  9.3};
		Vector<double> res = std::move(a) / 2.0;
		if(a.size()   != 0)          { err("operator/ test (r-value, scalar) [src size]"); }
		if(res.size() != 3)          { err("operator/ test (r-value, scalar) [size]");     }
		if(length(res - ref) > 1e-15){ err("operator/ test (r-value, scalar) [value]");    }
	}

	//Test dot:
	{
		Vector<double> a = {3.1, -5.1, 9.1};
		Vector<double> b = {2.0, -3.0, 6.0};
		double ref = 76.1;
		double res = dot(a, b);
		if(std::abs(ref-res))                         { err("dot test [value]");        }
		if(a.size() != 3)                             { err("dot test [src size]");     }
		if(b.size() != 3)                             { err("dot test [src size]");     }
		if(a[0] != 3.1 || a[1] != -5.1 || a[2] != 9.1){ err("dot test [src elements]"); }
		if(b[0] != 2.0 || b[1] != -3.0 || b[2] != 6.0){ err("dot test [src elements]"); }
	}

	//Test normalize (l-value)
	{
		Vector<double> a   = {9.0,  -12.0, 20.0};
		Vector<double> ref = {0.36, -0.48,  0.8};
		Vector<double> res = normalize(a);
		if(a.size()   != 3)                             { err("normalize test (l-value) [src size]");     }
		if(res.size() != 3)                             { err("normalize test (l-value) [size]");         }
		if(a[0] != 9.0 || a[1] != -12.0 || a[2] != 20.0){ err("normalize test (l-value) [src elements]"); }
		if(length(res - ref) > 1e-15)                   { err("normalize test (l-value) [value]");        }
	}

	//Test normalize (r-value)
	{
		Vector<double> a   = {9.0,  -12.0, 20.0};
		Vector<double> ref = {0.36, -0.48,  0.8};
		Vector<double> res = normalize(std::move(a));
		if(a.size()   != 0)                             { err("normalize test (r-value) [src size]"); }
		if(res.size() != 3)                             { err("normalize test (r-value) [size]");     }
		if(length(res - ref) > 1e-15)                   { err("normalize test (r-value) [value]");    }
	}

    std::cout << "All tests are successful!\n";
	return 0;
}