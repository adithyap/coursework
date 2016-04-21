#ifndef PAGER_FACTORY_HPP
#define PAGER_FACTORY_HPP

#include <iostream>

#include "pager.hpp"
#include "fcfs.hpp"
#include "second_chance.hpp"
#include "clock.hpp"
#include "clock_virtual.hpp"
#include "random_pager.hpp"
#include "lru.hpp"
#include "nru.hpp"
#include "aging.hpp"
#include "aging_virtual.hpp"

class PagerFactory
{
private:
    PagerFactory();

public:
    static Pager* get_pager(char*);

};

#endif // PAGER_FACTORY_HPP
