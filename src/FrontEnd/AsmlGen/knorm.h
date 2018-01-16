/**
 * \file      knorm.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     applies k_normalisation to the ptree given in argument
 *
 * \details
 */

#ifndef KNORM_H
#define KNORM_H

/**
 * \brief     k-normalises the given tree in input
 * \details   applies the following transformations :
 *            let v = (M1, ... Mn) in M => let v1 = x1 in ... in let v = (v1, ...,vn) in N
 *            let x = M in (N1, ...,Nn) => let x = M in let tup = (N1, ..., Nn) in tup
 *            let x = a op1 b op2 M => let v1 = a op1 b in let x = v1 op2 M
 *            let x = true/false => let x = 0/1
 *            let x = M arg1 ... argn => let v1 = M in let v1 = M in let w1 = arg1 ... in let x = v1 w1 ... wn
 *            let x = -(-M) => let x = M
 *            let x = not (0/1) => let x = 1/0
 *            let x = if true then M else N => let x = M (idem for false case)
 *            (M1, ..., Mn) => let v1 = M1 in ... let vn = Mn in (v1, ..., vn)
 *            let (x1, ..., xn) = M in N => let y = M in let (x1, ..., xn) = y in N
 *            let x = array M N => let v1 = M in let v2 = N in let x = array v1 v2
 *            let x = M(N) => let v1 = M in let v2 = N in let x = v1(v2)
 *            let x = M(N) <- O => let v1 = M in let v2 = N in let v3 = O in let x = v1(v2) <- v3
 *            other cases -> recursive application of knormalisation
 * \param     the ptree to k-normalise
 * \return    the k-normalised ptree
 */
ptree knorm(ptree t);

/**
 * \brief     recursive function k-normalising a T_APP tree node
 * \details   as specified in knorm
 * \param     the T_APP ptree node to k-normalise
 * \return    the k-normalised ptree
 */
ptree k_norm_t_app(ptree t, listNode *arg_node);

/**
 * \brief     recursive function k-normalising a T_TUPLE tree node
 * \details   as specified in knorm
 * \param     the T_TUPLE ptree node to k-normalise
 * \return    the k-normalised ptree
 */
ptree knorm_tuple(ptree t, listNode *arg_node);
#endif
