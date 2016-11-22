#!/usr/bin/env bash

rpl 'template<class T>' 'template<typename T>' Queue.h
rpl 'class' 'struct' Queue.h

rpl 'template<class T>' 'template<typename T>' LoopedArray.h
rpl 'class' 'struct' LoopedArray.h

rpl 'template<class T>' 'template<typename T>' QueueArray.h
rpl 'class' 'struct' QueueArray.h

rpl 'template<class T>' 'template<typename T>' QueueList.h
rpl 'class' 'struct' QueueList.h

rpl 'template<template<typename> class QUEUE>' 'template<template<typename> typename QUEUE>' ServiceUnit.h
rpl 'template<template<typename> class QUEUE_T>' 'template<template<typename> typename QUEUE_T>' ServiceUnit.h
rpl 'class' 'struct' ServiceUnit.h

rpl 'template<class T, template<typename> class QUEUE>' 'template<typename T, template<typename> typename QUEUE>' QueueTests.h
