#!/usr/bin/env bash

rpl 'template<class T>' 'template<typename T>' MatrixBase.h
rpl 'template<class I>' 'template<typename I>' MatrixBase.h
rpl 'template<class A, class B, class C>' 'template<typename A, typename B, typename C>' MatrixBase.h
rpl 'class' 'struct' MatrixBase.h

rpl 'template<class T>' 'template<typename T>' MatrixClassic.h
rpl 'template<class I>' 'template<typename I>' MatrixClassic.h
rpl 'class' 'struct' MatrixClassic.h

rpl 'template<class T>' 'template<typename T>' Generator.h
rpl 'template<class GENERATOR>' 'template<typename GENERATOR>' Generator.h
rpl 'class' 'struct' Generator.h

echo -n "'class' entries in MatrixBase.h: "
grep class < MatrixBase.h | wc -l

echo -n "'class' entries in MatrixClassic.h: "
grep class < MatrixClassic.h | wc -l

echo -n "'class' entries in Generator.h: "
grep class < Generator.h | wc -l