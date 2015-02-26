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

}

template <typename IteratorType1, typename IteratorType2,
          typename OutputIteratorType, typename BinaryOp, typename Less>
void zip_equal(IteratorType1 begin1, IteratorType1 end1,
               IteratorType2 begin2, IteratorType2 end2,
               OutputIteratorType output, BinaryOp op, Less less)
{
   IteratorType1 it1 = begin1;
   IteratorType2 it2 = begin2;

   while (it1 != end1 || it2 != end2)
   {
      if (it1 != end1 && it2 != end2)
      {
         if (less(*it1, *it2))
            output = op(&*(it1++), nullptr);
         else if (less(*it2, *it1))
            output = op(nullptr, &*(it2++));
         else
            output = op(&*(it1++), &*(it2++));
      }
      else if (it2 == end2)
         output = op(&*(it1++), nullptr);
      else
         output = op(nullptr, &*(it2++));
   }
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
