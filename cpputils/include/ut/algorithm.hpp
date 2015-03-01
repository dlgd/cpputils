#ifndef UT_ALGORITHM_HPP
#define UT_ALGORITHM_HPP

#include <functional>

namespace ut
{

namespace detail
{

struct less_t
{
   template <typename T1, typename T2>
   bool operator()(const T1& lhs, const T2& rhs) const
   {
      return lhs < rhs;
   }
};

template <typename BinaryOp>
struct zip_op_t
{
   zip_op_t(BinaryOp op):
      m_op(op)
   {}

   template <typename T1, typename T2, typename OutputIteratorType>
   OutputIteratorType operator()(OutputIteratorType output,
                                 T1 lhs, T2 rhs) const
   {
      *output = m_op(lhs, rhs);
      return ++output;
   }

   BinaryOp m_op;
};

}

template <typename IteratorType1, typename IteratorType2,
          typename T, typename BinaryOp, typename Less>
T fold_equal(IteratorType1 begin1, IteratorType1 end1,
             IteratorType2 begin2, IteratorType2 end2,
             T init, BinaryOp op, Less less)
{
   IteratorType1 it1 = begin1;
   IteratorType2 it2 = begin2;
   while (it1 != end1 || it2 != end2)
   {
      if (it2 == end2 || less(*it1, *it2))
         init = op(init, &*(it1++), nullptr);
      else if (it1 == end1 || less(*it2, *it1))
         init = op(init, nullptr, &*(it2++));
      else
         init = op(init, &*(it1++), &*(it2++));
   }
   return init;
}

template <typename IteratorType1, typename IteratorType2,
          typename T, typename BinaryOp>
T fold_equal(IteratorType1 begin1, IteratorType1 end1,
             IteratorType2 begin2, IteratorType2 end2,
             T init, BinaryOp op)
{
   fold_equal(begin1, end1, begin2, end2, init, op, detail::less_t());
}

template <typename IteratorType1, typename IteratorType2,
          typename OutputIteratorType, typename BinaryOp, typename Less>
void zip_equal(IteratorType1 begin1, IteratorType1 end1,
               IteratorType2 begin2, IteratorType2 end2,
               OutputIteratorType output, BinaryOp op, Less less)
{
   detail::zip_op_t<BinaryOp> zip_op(op);
   fold_equal(begin1, end1, begin2, end2, output, zip_op, less);
}

template <typename IteratorType1, typename IteratorType2,
          typename OutputIteratorType, typename BinaryOp>
void zip_equal(IteratorType1 begin1, IteratorType1 end1,
               IteratorType2 begin2, IteratorType2 end2,
               OutputIteratorType output, BinaryOp op)
{
   zip_equal(begin1, end1, begin2, end2, output, op, detail::less_t());
}

}

#endif
