/*
 *  Copyright 2008-2009 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*! \file csr_matrix.h
 *  \brief Compressed Sparse Row matrix format.
 */

#pragma once

#include <cusp/detail/config.h>

#include <cusp/array1d.h>
#include <cusp/format.h>
#include <cusp/detail/matrix_base.h>

namespace cusp
{

/*! \addtogroup containers Containers 
 *  \addtogroup sparse_matrix_formats Sparse Matrices
 *  \ingroup containers
 *  \{
 */

/*! \p csr_matrix : Compressed Sparse Row matrix container
 *
 * \tparam IndexType Type used for matrix indices (e.g. \c int).
 * \tparam ValueType Type used for matrix values (e.g. \c float).
 * \tparam MemorySpace A memory space (e.g. \c cusp::host_memory or cusp::device_memory)
 *
 * \note The matrix entries within the same row must be sorted by column index.
 * \note The matrix should not contain duplicate entries.
 *
 *  The following code snippet demonstrates how to create a 4-by-3
 *  \p csr_matrix on the host with 6 nonzeros and then copies the
 *  matrix to the device.
 *
 *  \code
 *  #include <cusp/csr_matrix.h>
 *  ...
 *
 *  // allocate storage for (4,3) matrix with 4 nonzeros
 *  cusp::csr_matrix<int,float,cusp::host_memory> A(4,3,6);
 *
 *  // initialize matrix entries on host
 *  A.row_offsets[0] = 0;  // first offset is always zero
 *  A.row_offsets[1] = 2;  
 *  A.row_offsets[2] = 2;  
 *  A.row_offsets[3] = 3;
 *  A.row_offsets[4] = 6; // last offset is always num_entries
 *
 *  A.column_indices[0] = 0; A.values[0] = 10; 
 *  A.column_indices[1] = 2; A.values[1] = 20;
 *  A.column_indices[2] = 2; A.values[2] = 30;
 *  A.column_indices[3] = 0; A.values[3] = 40;
 *  A.column_indices[4] = 1; A.values[4] = 50;
 *  A.column_indices[5] = 2; A.values[5] = 60;
 *
 *  // A now represents the following matrix
 *  //    [10  0 20]
 *  //    [ 0  0  0]
 *  //    [ 0  0 30]
 *  //    [40 50 60]
 *
 *  // copy to the device
 *  cusp::csr_matrix<int,float,cusp::device_memory> A = B;
 *  \endcode
 *
 */
template <typename IndexType, typename ValueType, class MemorySpace>
class csr_matrix : public detail::matrix_base<IndexType,ValueType,MemorySpace,cusp::csr_format>
{
  public:
    template<typename MemorySpace2>
    struct rebind { typedef cusp::csr_matrix<IndexType, ValueType, MemorySpace2> type; };
    
    // equivalent container type
    typedef typename cusp::csr_matrix<IndexType, ValueType, MemorySpace> container;

    typedef typename cusp::array1d<IndexType, MemorySpace> row_offsets_array_type;
    typedef typename cusp::array1d<IndexType, MemorySpace> column_indices_array_type;
    typedef typename cusp::array1d<ValueType, MemorySpace> values_array_type;
    
    /*! Storage for the row offsets of the CSR data structure.  Also called the "row pointer" array.
     */
    row_offsets_array_type row_offsets;
    
    /*! Storage for the column indices of the CSR data structure.
     */
    column_indices_array_type column_indices;
    
    /*! Storage for the nonzero entries of the CSR data structure.
     */
    values_array_type values;


    /*! Construct an empty \p csr_matrix.
     */
    csr_matrix();

    /*! Construct a \p csr_matrix with a specific shape and number of nonzero entries.
     *
     *  \param num_rows Number of rows.
     *  \param num_cols Number of columns.
     *  \param num_entries Number of nonzero matrix entries.
     */
    csr_matrix(IndexType num_rows, IndexType num_cols, IndexType num_entries);

    /*! Construct a \p csr_matrix from another matrix.
     *
     *  \param matrix Another sparse or dense matrix.
     */
    template <typename MatrixType>
    csr_matrix(const MatrixType& matrix);
    
    void resize(IndexType num_rows, IndexType num_cols, IndexType num_entries);

    /*! Swap the contents of two \p csr_matrix objects.
     *
     *  \param matrix Another \p csr_matrix with the same IndexType and ValueType.
     */
    void swap(csr_matrix& matrix);
    
    /*! Assignment from another matrix.
     *
     *  \param matrix Another sparse or dense matrix.
     */
    template <typename MatrixType>
    csr_matrix& operator=(const MatrixType& matrix);
}; // class csr_matrix
/*! \}
 */


/*! \addtogroup views Views
 *  \addtogroup sparse_matrix_formats Sparse Matrices
 *  \ingroup views
 *  \{
 */

/*! \p csr_matrix_view : Compressed Sparse Row (CSR) matrix view
 *
 * TODO document
 *
 */
template <typename Array1,
          typename Array2,
          typename Array3,
          typename IndexType   = typename Array1::value_type,
          typename ValueType   = typename Array3::value_type,
          typename MemorySpace = typename cusp::minimum_space<typename Array1::memory_space, typename Array2::memory_space, typename Array3::memory_space>::type >
          class csr_matrix_view : public cusp::detail::matrix_base<IndexType,ValueType,MemorySpace,cusp::csr_format>
{
  typedef cusp::detail::matrix_base<IndexType,ValueType,MemorySpace,cusp::csr_format> Parent;
  public:
    // equivalent container type
    typedef typename cusp::csr_matrix<IndexType, ValueType, MemorySpace> container;

    typedef Array1 row_offsets_array_type;
    typedef Array2 column_indices_array_type;
    typedef Array3 values_array_type;

    /*! Storage for the row offsets of the CSR data structure.  Also called the "row pointer" array.
     */
    row_offsets_array_type row_offsets;
    
    /*! Storage for the column indices of the CSR data structure.
     */
    column_indices_array_type column_indices;
    
    /*! Storage for the nonzero entries of the CSR data structure.
     */
    values_array_type values;

    // construct empty view
    csr_matrix_view(void)
      : Parent() {}

    // construct from existing CSR matrix or view
    template <typename Matrix>
    csr_matrix_view(Matrix& A)
      : Parent(A),
        row_offsets(A.row_offsets),
        column_indices(A.column_indices),
        values(A.values) {}

    // TODO check sizes here
    csr_matrix_view(IndexType num_rows,
                    IndexType num_cols,
                    IndexType num_entries,
                    Array1 row_offsets,
                    Array2 column_indices,
                    Array3 values)
      : Parent(num_rows, num_cols, num_entries),
        row_offsets(row_offsets),
        column_indices(column_indices),
        values(values) {}

    void resize(IndexType num_rows, IndexType num_cols, IndexType num_entries)
    {
      Parent::resize(num_rows, num_cols, num_entries);
      row_offsets.resize(num_rows + 1);
      column_indices.resize(num_entries);
      values.resize(num_entries);
    }
};

/* Convenience functions */

template <typename IndexType,
          typename Array1,
          typename Array2,
          typename Array3>
csr_matrix_view<Array1,Array2,Array3,IndexType>
make_csr_matrix_view(IndexType num_rows,
                     IndexType num_cols,
                     IndexType num_entries,
                     Array1 row_offsets,
                     Array2 column_indices,
                     Array3 values)
{
  return csr_matrix_view<Array1,Array2,Array3,IndexType>
    (num_rows, num_cols, num_entries,
     row_offsets, column_indices, values);
}

template <typename Array1,
          typename Array2,
          typename Array3,
          typename IndexType,
          typename ValueType,
          typename MemorySpace>
csr_matrix_view<Array1,Array2,Array3,IndexType,ValueType,MemorySpace>
make_csr_matrix_view(const csr_matrix_view<Array1,Array2,Array3,IndexType,ValueType,MemorySpace>& m)
{
  return csr_matrix_view<Array1,Array2,Array3,IndexType,ValueType,MemorySpace>(m);
}
    
template <typename IndexType, typename ValueType, class MemorySpace>
csr_matrix_view < cusp::array1d_view< typename cusp::array1d<IndexType,MemorySpace>::iterator >,
                  cusp::array1d_view< typename cusp::array1d<IndexType,MemorySpace>::iterator >,
                  cusp::array1d_view< typename cusp::array1d<ValueType,MemorySpace>::iterator >,
                  IndexType, ValueType, MemorySpace>
make_csr_matrix_view(csr_matrix<IndexType,ValueType,MemorySpace>& m)
{
  return make_csr_matrix_view
    (m.num_rows, m.num_cols, m.num_entries,
     make_array1d_view(m.row_offsets),
     make_array1d_view(m.column_indices),
     make_array1d_view(m.values));
}

template <typename IndexType, typename ValueType, class MemorySpace>
csr_matrix_view < cusp::array1d_view< typename cusp::array1d<IndexType,MemorySpace>::const_iterator >,
                  cusp::array1d_view< typename cusp::array1d<IndexType,MemorySpace>::const_iterator >,
                  cusp::array1d_view< typename cusp::array1d<ValueType,MemorySpace>::const_iterator >,
                  IndexType, ValueType, MemorySpace>
make_csr_matrix_view(const csr_matrix<IndexType,ValueType,MemorySpace>& m)
{
  return make_csr_matrix_view
    (m.num_rows, m.num_cols, m.num_entries,
     make_array1d_view(m.row_offsets),
     make_array1d_view(m.column_indices),
     make_array1d_view(m.values));
}
/*! \}
 */

} // end namespace cusp

#include <cusp/detail/csr_matrix.inl>

