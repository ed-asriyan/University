#!/usr/bin/env bash

rpl 'template<class T>' 'template<typename T>' MatrixBase.h
rpl 'template<class I>' 'template<typename I>' MatrixBase.h
rpl 'template<class A, class B, class C>' 'template<typename A, typename B, typename C>' MatrixBase.h
rpl 'class' 'struct' MatrixBase.h

rpl 'template<class T>' 'template<typename T>' ClassicMatrix.h
rpl 'template<class I>' 'template<typename I>' ClassicMatrix.h
rpl 'class' 'struct' ClassicMatrix.h

rpl 'template<class T>' 'template<typename T>' SparseMatrix.h
rpl 'class' 'struct' SparseMatrix.h

rpl 'template<class T>' 'template<typename T>' SparseMatrixOptimized.h
rpl 'class' 'struct' SparseMatrixOptimized.h

rpl 'template<class T>' 'template<typename T>' Generator.h
rpl 'template<class GENERATOR>' 'template<typename GENERATOR>' Generator.h
rpl 'template<class T, class DISTRIBUTION>' 'template<typename T, typename DISTRIBUTION>' Generator.h
rpl 'class' 'struct' Generator.h

rpl 'template<class A, class B>' 'template<typename A, typename B>' Helper.h

echo -n "'class' entries in MatrixBase.h: "
grep class -w < MatrixBase.h | wc -l

echo -n "'class' entries in ClassicMatrix.h: "
grep class -w < ClassicMatrix.h | wc -l

echo -n "'class' entries in SparseMatrix.h: "
grep class -w < SparseMatrix.h | wc -l

echo -n "'class' entries in SparseMatrixOptimized.h: "
grep class -w < SparseMatrixOptimized.h | wc -l

echo -n "'class' entries in Generator.h: "
grep class -w < Generator.h | wc -l

echo -n "'class' entries in Helper.h: "
grep class -w < Helper.h | wc -l

echo -n "'class' entries in main.cpp: "
grep class -w < main.cpp | wc -l