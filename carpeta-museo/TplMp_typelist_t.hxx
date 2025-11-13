#ifndef TPLMP_TYPELIST_T_HXX_INCLUDED
#define TPLMP_TYPELIST_T_HXX_INCLUDED

#include <tuple>

namespace TplMp {  /// BEGIN OF TPLMP NAMESPACE

using empty_tuple_t = std::tuple<>;
struct nil_t {};

template<typename ... Ts>
  requires (std::is_default_constructible_v<Ts>&&...&&true)
struct typelist_t;

template<typename ... Ts>
struct cat_impl {
  using type = typename typelist_t<Ts...>;
};
template<typename ... Ts>
using cat_t = typename cat_impl<Ts...>::type;

template<typename ... Zs>
struct cat_impl {
  template<typename ... As>
  struct cat_inner_impl {
    using type = typename typelist_t<As...,Zs...>
  };
  template<typename ... As>
  using type = typename cat_inner_impl<As...>::type;
};
template<typename ... As,typename ... Zs>
using cat_t = typename cat_impl<Zs...>::type<As...>;

template<>
using cat_t<nil_t,Rs...,S,Ts...> = typelist_t<Rs...,S,Ts...>;
template<>
using cat_t<Rs...,nil_t,S,Ts...> = typelist_t<Rs...,S,Ts...>;
template<>
using cat_t<Rs...,S,nil_t,Ts...> = typelist_t<Rs...,S,Ts...>;
template<>
using cat_t<empty_tuple_t,Rs...,S,Ts...> = typelist_t<Rs...,S,Ts...>;
template<>
using cat_t<Rs...,empty_tuple_t,S,Ts...> = typelist_t<Rs...,S,Ts...>;
template<>
using cat_t<Rs...,S,empty_tuple_t,Ts...> = typelist_t<Rs...,S,Ts...>;
template<>
using cat_t<typelist_t<>,Rs...,S,Ts...> = typelist_t<Rs...,S,Ts...>;
template<>
using cat_t<Rs...,typelist_t<>,S,Ts...> = typelist_t<Rs...,S,Ts...>;
template<>
using cat_t<Rs...,S,typelist_t<>,Ts...> = typelist_t<Rs...,S,Ts...>;

template<>
using cat_t<nil_t,Ts...> = typelist_t<Ts...>;
template<>
using cat_t<empty_tuple_t,Ts...> = typelist_t<Ts...>;
template<>
using cat_t<typelist_t<>,Ts...> = typelist_t<Ts...>;

template<>
using cat_t<T,nil_t,Ts...> = typelist_t<T,Ts...>;
template<>
using cat_t<T,empty_tuple_t,Ts...> = typelist_t<T,Ts...>;
template<>
using cat_t<T,typelist_t<>,Ts...> = cat_t<typelist_t<T>,typelist_t<Ts...>>;

template<>
struct typelist_t<> : public empty_tuple_t  {
  static consteval std::size_t sz() noexcept {return 0;}

  using tuple_t  =  empty_tuple_t;

  using head_t   =  nil_t;
  static constexpr long long int head_idx = -1;
  using tail_t   =  empty_tuple_t;

  using shead_t  =  nil_t;
  static constexpr long long int shead_idx = -1;

  using body_t   =  empty_tuple_t;
  using head_middle_t =  nil_t;
  static constexpr long long int head_middle_idx = -1;
  using middle_t =  nil_t;
  static constexpr long long int middle_idx = -1;
  using last_middle_t =  nil_t;
  static constexpr long long int last_middle_idx = -1;

  using slast_t  =  nil_t;
  static constexpr long long int slast_idx = -1;

  using init_t   =  empty_tuple_t;
  using last_t   =  nil_t;
  static constexpr long long int slat_idx = -1;
};

template<std::size_t Idx>
struct get {
  template<typename ...As,typename T, typename ...Zs>
  struct internal_using {
    using typelist = typename typelist_t<As...,T,Zs...>;

    using type =
      std::conditional_t<//open main angular parenthesis main if 0
        typelist::sz() > Idx,
          std::conditional_t<//open angular parenthesis main case 1
            typelist::sz()==0,
              nil_t,
          std::conditional_t<//open angular parenthesis main case 2
            typelist::sz()==1,
              std::conditional_t<Idx==0,typename typelist::head_t,
              nil_t// default
              >,// main case 1
          std::conditional_t<//open angular parenthesis main case 3
            typelist::sz()==2,
              std::conditional_t<Idx==0,typename typelist::head_t,
              std::conditional_t<Idx==1,typename typelist::last_t,
              nil_t//default
              >>,// main case 2
          std::conditional_t<//open angular parenthesis main case 4
            typelist::sz()==3,
              std::conditional_t<Idx==0,typename typelist::head_t,
              std::conditional_t<Idx==1,typename typelist::middle_t,
              std::conditional_t<Idx==2,typename typelist::last_t,
              nil_t//default
              >>>,// main case 3
          std::conditional_t<//open angular parenthesis main case 5
            typelist_t::sz()==4,
              std::conditional_t<Idx==0,typename typelist::head_t,
              std::conditional_t<Idx==1,typename typelist::shead_t,
              std::conditional_t<Idx==2,typename typelist::slast_t,
              std::conditional_t<Idx==3,typename typelist::last_t,
              nil_t//default
              >>>>,// main case 4
          std::conditional_t<//open angular parenthesis main case 6
            typelist::sz()==5,
              std::conditional_t<Idx==0,typename typelist::head_t,
              std::conditional_t<Idx==1,typename typelist::shead_t,
              std::conditional_t<Idx==2,typename typelist::middle_t,
              std::conditional_t<Idx==3,typename typelist::slast_t,
              std::conditional_t<Idx==4,typename typelist::last_t,
              nil_t//default
              >>>>>,// main case 5
          std::conditional_t<//open angular parenthesis main case 7
            typelist_t::sz()==6,
              std::conditional_t<Idx==0,typename typelist::head_t,
              std::conditional_t<Idx==1,typename typelist::shead_t,
              std::conditional_t<Idx==2,typename typelist::left_middle_t,
              std::conditional_t<Idx==3,typename typelist::right_middle_t,
              std::conditional_t<Idx==4,typename typelist::slast_t,
              std::conditional_t<Idx==5,typename typelist::last_t,
              nil_t//default
              >>>>>>,// main case 6
          std::conditional_t<//open angular parenthesis main case 8
            typelist_t::sz()==7,
              std::conditional_t<Idx==0,typename typelist::head_t,
              std::conditional_t<Idx==1,typename typelist::shead_t,
              std::conditional_t<Idx==2,typename typelist::left_middle_t,
              std::conditional_t<Idx==3,typename typelist::middle_t,
              std::conditional_t<Idx==4,typename typelist::right_middle_t,
              std::conditional_t<Idx==5,typename typelist::slast_t,
              std::conditional_t<Idx==6,typename typelist::last_t,
              nil_t//default
              >>>>>>>,// main case 7
          std::conditional_t<//open angular parenthesis main case 9
            ( ( typelist::sz() % 2 ) == 1 ) && ( Idx >= typelist::sz() ),
              std::conditional_t<Idx==typelist::middle_idx,typename typelist::middle_t,
              std::conditional_t<Idx==0,typename typelist::head_t,
              std::conditional_t<Idx==1,typename typelist::shead_t,
              std::conditional_t<Idx==typelist::sz()-1,typename typelist::last_t,
              std::conditional_t<Idx==typelist::sz()-2,typename typelist::slast_t,
              std::conditional_t<Idx == arg_typelist_t::middle_idx-1,typename typelist::left_middle_t,
              std::conditional_t<Idx == arg_typelist_t::middle_idx+1,typename typelist::right_middle_t,
              std::conditional_t<Idx < arg_typelist_t::middle_idx-1,typename typelist::first_pack::get<Idx>::type,
              std::conditional_t<Idx > arg_typelist_t::middle_idx+1,typename typelist::last_pack::get<Idx-(Idx/2)>::type,
              nil_t//default
              >>>>>>>>>,// main case 9
          std::conditional_t<//open angular parenthesis main case 10
            ( ( typelist::sz() % 2 ) == 0 ) && ( Idx >= typelist::sz() ),
              std::conditional_t<Idx==0,typename typelist::head_t,
              std::conditional_t<Idx==1,typename typelist::shead_t,
              std::conditional_t<Idx==typelist::sz()-1,typename typelist::last_t,
              std::conditional_t<Idx==typelist::sz()-2,typename typelist::slast_t,
              std::conditional_t<Idx == arg_typelist_t::left_middle_idx,typename typelist::left_middle_t,
              std::conditional_t<Idx == arg_typelist_t::right_middle_idx,typename typelist::right_middle_t,
              std::conditional_t<Idx < arg_typelist_t::left_middle_idx,typename typelist::first_pack::get<Idx>::type,
              std::conditional_t<Idx > arg_typelist_t::right_middle_idx,typename typelist::last_pack::get<Idx-(Idx/2)>::type,
              nil_t//default
              >>>>>>>>// close main case 8
        >//close angular parenthesis main case 10
        >//close angular parenthesis main case 9
        >//close angular parenthesis main case 8
        >//close angular parenthesis main case 7
        >//close angular parenthesis main case 6
        >//close angular parenthesis main case 5
        >//close angular parenthesis main case 4
        >//close angular parenthesis main case 3
        >//close angular parenthesis main case 2
        >//close angular parenthesis main case 1
        ,nil_t // default main
      >  //close angular parenthesis main if 0
      ;
  };
};

template<std::size_t Idx,typename ...As,typename T,typename ...Zs>
using typelist_elem_t = typename get<Idx>::internal_using<As...,T,Zs...>::type;

template<> using cat_t<empty_tuple_t> = typelist_t<>;
template<> using cat_t<empty_tuple_t,empty_tuple_t> = typelist_t<>;
template<> using cat_t<empty_tuple_t,nil_t> = typelist_t<>;
template<> using cat_t<nil_t,empty_tuple_t> = typelist_t<>;
template<> using cat_t<empty_tuple_t,typelist_t<>> = typelist_t<>;
template<> using cat_t<typelist_t<>,empty_tuple_t> = typelist_t<>;
template<> using cat_t<nil_t,nil_t> = typelist_t<>;
template<> using cat_t<typelist_t<>,typelist_t<>> = typelist_t<>;
template<> using cat_t<nil_t,typelist_t<>> = typelist_t<>;
template<> using cat_t<typelist_t<>,nil_t> = typelist_t<>;
template<> using cat_t<nil_t>  = typelist_t<>;
template<> using cat_t<typelist_t<>>  = typelist_t<>;
template<> using cat_t<>  = typelist_t<>;


template<typename ... As, typename T, typename ... Zs>
  requires(
            (sizeof...(Zs)>2)
            &&
            (sizeof...(As)>2)
            &&
            std::is_default_constructible_v<T>
            &&
            (std::is_default_constructible_v<As>&&...&&true)
            &&
            (std::is_default_constructible_v<Zs>&&...&&true)
          )
struct typelist_t<As...,T,Zs...> :
    public cat_t<cat_t<As...>::tail_t,T,cat_t<Zs...>        >,// the tail
    public cat_t<cat_t<As...>        ,T,cat_t<Zs...>::init_t>,// the init
    public cat_t<cat_t<As...>::tail_t,T,cat_t<Zs...>::init_t> // the body
{
  using inhered_tail = cat_t<cat_t<As...>::tail_t,T,cat_t<Zs...>        >;
  using inhered_init = cat_t<cat_t<As...>        ,T,cat_t<Zs...>::init_t>;
  using inhered_body = cat_t<cat_t<As...>::tail_t,T,cat_t<Zs...>::init_t>;
  using first_pack   = cat_t<As...>;
  using last_pack    = cat_t<Zs...>;
  using init_t       = inhered_init;
  using tail_t       = inhered_tail;
  using body_t       = inhered_body;

  static consteval std::size_t sz() noexcept {return (tail_t::sz()+1);}

  using tuple_t = std::tuple<As...,T,Zs...>;

  using head_t =  typename first_pack::head_t;
  static constexpr std::size_t head_idx = 0;

  using shead_t = typename tail_t::head_t;
  static constexpr std::size_t shead_idx = 1;

  using middle_t =  typename std::conditional_t<
                      sz()%2==0,
                        nil_t,
                        typename body_t::middle_t
                    >;
  static constexpr long long int middle_idx = sz()%2==0 ? -1 : ((sz()-1)/2);

  using left_middle_t = typename body_t::left_middle_t;
  static constexpr long long int left_middle_idx = (sz()/2)-1;
  using right_middle_t =  typename body_t::right_middle_t;
  static constexpr long long int right_middle_idx = (sz()+1)/2;

  using slast_t = typename tail_t::slast_t;
  static constexpr long long int slast_idx = sz()-2;


  using last_t =  typename tail_t::last_t;
  static constexpr long long int last_idx = sz()-1;
};

template<typename P,typename Q,typename R, typename S, typename T, typename U>
  requires (std::is_default_constructible_v<P>)
struct typelist_t<P,Q,R,S,T> : public cat_t<P,Q,R,S,T>,
                               public cat_t<Q,R,S,T,U>,
                               public cat_t<Q,R,S,T>                   {

  using first_pack   = cat_t<P,Q,R>;
  using last_pack    = cat_t<S,T,U>;
  static consteval std::size_t sz() noexcept {return 6;}

  using tuple_t   =  std::tuple<P,Q,R,S,T,U>;

  using head_t    =  P;
  static constexpr long long int head_idx = 0;
  using tail_t    =  typelist_t<Q,R,S,T,U>;/// una de las metaclases base heredadas

  using shead_t   =  Q;
  static constexpr long long int shead_idx = 1;
  using body_t    =  typelist_t<Q,R,S,T>;  /// una de las metaclases base heredadas
  using left_middle_t = R;
  static constexpr long long int left_middle_idx = 2;
  using middle_t  =  nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t = S;
  static constexpr long long int right_middle_idx = 3;
  using slast_t   =  T;
  static constexpr long long int slast_idx = 4;

  using init_t    =  typelist_t<P,Q,R,S,T>;/// una de las metaclases base heredadas
  using last_t    =  U;
  static constexpr long long int last_idx = 5;
};

template<typename P,typename Q,typename R, typename S, typename T>
  requires (std::is_default_constructible_v<P>)
struct typelist_t<P,Q,R,S,T> : public cat_t<Q,R,S,T>,
                               public cat_t<P,Q,R,S>,
                               public cat_t<Q,R,S>                   {
  using first_pack   = cat_t<P,Q>;
  using last_pack    = cat_t<S,T>;
  static consteval std::size_t sz() noexcept {return 5;}

  using tuple_t   =  std::tuple<P,Q,R,S,T>;

  using head_t    =  P;
  static constexpr long long int head_idx = 0;
  using tail_t    =  typelist_t<Q,R,S,T>;/// una de las metaclases base heredadas

  using shead_t   =  Q;
  static constexpr long long int shead_idx = 1;
  using body_t    =  typelist_t<Q,R,S>;  /// una de las metaclases base heredadas
  using left_middle_t = nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t  =  R;
  static constexpr long long int middle_idx = 2;
  using right_middle_t = nil_t;
  static constexpr long long int right_middle_idx = -1;
  using slast_t   =  S;
  static constexpr long long int slast_idx = 3;

  using init_t    =  typelist_t<P,Q,R,S>;/// una de las metaclases base heredadas
  using last_t    =  T;
  static constexpr long long int last_idx = 4;
};
// 00000 =   0  --  0
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,R,S,T>  = typelist_t<P,Q,R,S,T>;
// 00001 =   1  --  1
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,R,S,typelist_t<T>>  = typelist_t<P,Q,R,S,T>;
// 00010 =   5  --  2
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,R,typelist_t<S>,T>  = typelist_t<P,Q,R,S,T>;
// 00100 =  25  --  3
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,typelist_t<R>,S,T>  = typelist_t<P,Q,R,S,T>;
// 01000 ==125   --  4
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,R,S,T>  = typelist_t<P,Q,R,S,T>;
// 10000 ==625  --  5
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,R,S,T>  = typelist_t<P,Q,R,S,T>;
// 00011 ==  6  --  6
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,R,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 00101 == 26  --  7
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,typelist_t<R>,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 01001 ==126  --  8
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,R,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 10001 ==626  --  9
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,R,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 00110 == 30  -- 10
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,typelist_t<R>,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 01010 ==130  -- 11
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,R,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 10010 ==630  -- 12
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,R,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 01100 ==150  -- 13
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,typelist_t<R>,S,T> = typelist_t<P,Q,R,S,T>;
// 10100 ==650  -- 14
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,typelist_t<R>,S,T> = typelist_t<P,Q,R,S,T>;
// 11000 ==750  -- 15
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,R,S,T> = typelist_t<P,Q,R,S,T>;
// 00111 == 31  -- 16
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,typelist_t<R>,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 01011 ==131  -- 17
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,R,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 10011 ==631  -- 18
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,R,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 01110 ==155  -- 19
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,typelist_t<R>,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 10110 ==655  -- 20
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,typelist_t<R>,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 11100 ==775  -- 21
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R>,S,T> = typelist_t<P,Q,R,S,T>;
// 01111 ==156  -- 22
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,typelist_t<R>,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 10111 ==656  -- 23
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,typelist_t<R>,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 11011 ==756  -- 24
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,R,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 11101 ==776  -- 25
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R>,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 11110 ==780  -- 26
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R>,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 11111 ==781  -- 27
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R>,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 0002  ==  2  -- 28
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,R,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 0012  ==  7  -- 29
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,typelist_t<R>,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 0102  == 27  -- 30
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,R,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 1002  ==127  -- 31
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,R,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 0112  ==132  -- 32
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,typelist_t<R>,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 1012  ==632  -- 33
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,typelist_t<R>,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 1102  ==132  -- 34
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,R,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 1112  ==157  -- 35
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R>,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 122   == 37  -- 36
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q,R>,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 022   == 12  --  37
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q,R>,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 212  == 57  --  38
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,typelist_t<R>,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 202  == 52  --  39
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,R,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
// 221  == 61  -- 40
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,typelist_t<R,S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 220  == 60  -- 41
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,typelist_t<R,S>,T> = typelist_t<P,Q,R,S,T>;
// 0020 == 10  -- 42
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,typelist_t<R,S>,T> = typelist_t<P,Q,R,S,T>;
// 0021 == 11  --  43
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,typelist_t<R,S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 0120 == 35  --  44
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,typelist_t<R,S>,T> = typelist_t<P,Q,R,S,T>;
// 1020 ==135  --  45
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,typelist_t<R,S>,T> = typelist_t<P,Q,R,S,T>;
// 0121 == 36  --  46
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,typelist_t<R,S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 1021 ==136  --  47
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,typelist_t<R,S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 1120 ==160  --  48
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R,S>,T> = typelist_t<P,Q,R,S,T>;
// 1121 ==161  --  49
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R,S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 0200 == 50  --  50
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q,R>,S,T> = typelist_t<P,Q,R,S,T>;
// 0201 == 51  --  51
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q,R>,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 0210 == 55  --  52
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q,R>,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 1200 ==135  --  53
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q,R>,S,T> = typelist_t<P,Q,R,S,T>;
// 0211 == 56  --  54
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q,R>,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 1201 ==176  --  55
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q,R>,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 1210 ==180  --  56
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q,R>,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 1211 ==181  --  57
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q,R>,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 2000 ==250  --  58
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,R,S,T> = typelist_t<P,Q,R,S,T>;
// 2001 ==251  --  59
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,R,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 2010 ==255  --  60
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,R,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 2100 ==275  --  61
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,typelist_t<R>,S,T> = typelist_t<P,Q,R,S,T>;
// 2011 ==256  --  62
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,R,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 2101 ==276  --  63
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,typelist_t<R>,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 2110 ==280  --  64
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,typelist_t<R>,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
// 2111 ==281  --  65
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,typelist_t<R>,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 003  ==  3  --  66
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,Q,typelist_t<R,S,T>> = typelist_t<P,Q,R,S,T>;
// 013  ==  8  --  67
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q>,typelist_t<R,S,T>> = typelist_t<P,Q,R,S,T>;
// 103  == 28  --  68
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,Q,typelist_t<R,S,T>> = typelist_t<P,Q,R,S,T>;
// 113  == 33  --  69
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R,S,T>> = typelist_t<P,Q,R,S,T>;
//  23  == 13  --  70
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q>,typelist_t<R,S,T>> = typelist_t<P,Q,R,S,T>;
// 030  == 15  --  71
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q,R,S>,T> = typelist_t<P,Q,R,S,T>;
// 031  == 16  --  72
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q,R,S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 131  == 41  --  73
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q,R,S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 130  == 40  --  74
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q,R,S>,T> = typelist_t<P,Q,R,S,T>;
// 300  == 75  --  75
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q,R>,S,T> = typelist_t<P,Q,R,S,T>;
// 301  == 76  --  76
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q,R>,S,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 311  == 81  --  77
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q,R>,typelist_t<S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
// 310  == 80  --  78
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q,R>,typelist_t<S>,T> = typelist_t<P,Q,R,S,T>;
//  32  == 17  --  79
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q,R>,typelist_t<S,T>> = typelist_t<P,Q,R,S,T>;
//  04  ==  4  --  80
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<P,typelist_t<Q,R,S,T>> = typelist_t<P,Q,R,S,T>;
//  14  ==  9  --  81
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P>,typelist_t<Q,R,S,T>> = typelist_t<P,Q,R,S,T>;
//  40  == 20  --  82
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q,R,S>,T> = typelist_t<P,Q,R,S,T>;
//  41  == 21  --  83
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q,R,S>,typelist_t<T>> = typelist_t<P,Q,R,S,T>;
//   5  ==  5  --  84
template<typename P,typename Q,typename R,typename S,typename T>
using cat_t<typelist_t<P,Q,R,S,T>> = typelist_t<P,Q,R,S,T>;

template<typename P,typename Q,typename R, typename S>
  requires (std::is_default_constructible_v<P>)
struct typelist_t<P,Q,R,S> : public cat_t<Q,R,S>,
                             public cat_t<P,Q,R>,
                             public cat_t<Q,R>                         {
  using first_pack   = cat_t<P,Q>;
  using last_pack    = cat_t<R,S>;
  static consteval std::size_t sz() noexcept {return 4;}

  using tuple_t =  std::tuple<P,Q,R,S>;

  using head_t  =  P;
  static constexpr long long int head_idx = 0;
  using tail_t  =  typelist_t<Q,R,S>;/// una de las metaclases base heredadas

  using shead_t =  Q;
  static constexpr long long int shead_idx = 1;
  using body_t  =  typelist_t<Q,R>;  /// una de las metaclases base heredadas
  using left_middle_t = nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t=  nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t = nil_t;
  static constexpr long long int right_middle_idx = -1;
  using slast_t =  R;
  static constexpr long long int slast_idx = 2;

  using init_t  =  typelist_t<P,Q,R>;/// una de las metaclases base heredadas
  using last_t  =  S;
  static constexpr long long int last_idx = 3;
};

template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,R,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,typelist_t<R>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<Q>,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,Q,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,typelist_t<R>,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<Q>,R,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,Q,R,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<Q>,typelist_t<R>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,Q,typelist_t<R>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,typelist_t<Q>,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<Q>,typelist_t<R>,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,Q,typelist_t<R>,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,typelist_t<Q>,R,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R>,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,typelist_t<R,S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<Q,R>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P,Q>,R,S> = typelist_t<P,Q,R,S>;

template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<Q>,typelist_t<R,S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,Q,typelist_t<R,S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,typelist_t<Q>,typelist_t<R,S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<Q,R>,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,typelist_t<Q,R>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,typelist_t<Q,R>,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P,Q>,R,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P,Q>,typelist_t<R>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P,Q>,typelist_t<R>,typelist_t<S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P,Q>,typelist_t<R,S>> = typelist_t<P,Q,R,S>;

template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,R,S,nil_t> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,R,nil_t,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,nil_t,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,nil_t,Q,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<nil_t,P,Q,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,R,S,empty_tuple_t> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,R,empty_tuple_t,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,empty_tuple_t,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,empty_tuple_t,Q,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<empty_tuple_t,P,Q,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,R,S,typelist_t<>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,R,typelist_t<>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,Q,typelist_t<>,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<>,Q,R,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<>,P,Q,R,S> = typelist_t<P,Q,R,S>;

template<typename P,typename Q,typename R,typename S>
using cat_t<P,typelist_t<Q,R,S>> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P>,typelist_t<Q,R,S>> = typelist_t<P,Q,R,S>;

template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P,Q,R>,S> = typelist_t<P,Q,R,S>;
template<typename P,typename Q,typename R,typename S>
using cat_t<typelist_t<P,Q,R>,typelist_t<S>> = typelist_t<P,Q,R,S>;

template<typename T,typename R,typename S>
  requires (std::is_default_constructible_v<T>)
struct typelist_t<T,R,S> : public cat_t<T,R>,
                           public cat_t<R,S>,
                           public cat_t<R> {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 3;}

  using tuple_t = std::tuple<T,R,S>;

  using head_t =  T;
  static constexpr long long int head_idx = 0;
  using tail_t =  typelist_t<R,S>;/// una de las metaclases base heredadas

  using shead_t = R;
  static constexpr long long int head_idx = 1;
  using body_t =  typelist_t<R>;  /// una de las metaclases base heredadas
  using left_middle_t = nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t = R;
  static constexpr long long int middle_idx = 1;
  using right_middle_t = nil_t;
  static constexpr long long int right_middle_idx = -1;
  using slast_t = R;
  static constexpr long long int slast_idx = 1;

  using init_t =  typelist_t<T,R>;/// una de las metaclases base heredadas
  using last_t =  S;
  static constexpr long long int last_idx = 2;
};

template<typename T,typename R,typename S>
using cat_t<T,R,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<typelist_t<T>,typelist_t<R>,typelist_t<S>> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,typelist_t<R>,typelist_t<S>> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<typelist_t<T>,R,typelist_t<S>> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<typelist_t<T>,typelist_t<R>,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<typelist_t<T,R>,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<typelist_t<T,R>,typelist_t<S>> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,typelist_t<R,S>> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<typelist_t<T>,typelist_t<R,S>> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,R,S,nil_t> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,R,nil_t,S> typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,nil_t,R,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<nil_t,T,R,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,R,S,empty_tuple_t> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,R,empty_tuple_t,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,empty_tuple_t,R,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<empty_tuple_t,T,R,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,R,S,typelist_t<>> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,R,typelist_t<>,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<T,typelist_t<>,R,S> = typelist_t<T,R,S>;

template<typename T,typename R,typename S>
using cat_t<typelist_t<>,T,R,S> = typelist_t<T,R,S>;

template<typename T,typename R>
  requires (std::is_default_constructible_v<T>)
struct typelist_t<T,R> : public typelist_t<R> {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 2;}

  using tuple_t = std::tuple<T,R>;

  using head_t =  T;
  static constexpr long long int head_idx = 0;
  using tail_t =  typelist_t<R>;

  using shead_t = nil_t;
  static constexpr long long int shead_idx = 1;

  using body_t =  empty_tuple_t;
  using left_middle_t = nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t = nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t = nil_t;
  static constexpr long long int right_middle_idx = -1;

  using slast_t = nil_t;
  static constexpr long long int shead_idx = 0;

  using init_t =  typelist_t<T>;
  using last_t =  R;
  static constexpr long long int last_idx = 1;
};

template<typename T,typename R>
using cat_t<T,R> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<T,typelist_t<R>> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<typelist_t<T>,typelist_t<R>> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<typelist_t<T>,R> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<T,R,nil_t> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<T,nil_t,R> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<nil_t,T,R> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<T,R,empty_tuple_t> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<T,empty_tuple_t,R> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<empty_tuple_t,T,R> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<T,R,typelist_t<>> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<T,typelist_t<>,R> = typelist_t<T,R>;

template<typename T,typename R>
using cat_t<typelist_t<>,T,R> = typelist_t<T,R>;

template<typename T>
  requires (std::is_default_constructible_v<T>)
struct typelist_t<T> : public typelist_t<> {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 1;}

  using tuple_t = typename cat_t<T>::tuple_t;

  using head_t =  T;
  static constexpr long long int head_idx = 0;
  using tail_t =  empty_tuple_t;

  using shead_t = nil_t;
  static constexpr long long int shead_idx = -1;

  using body_t =  empty_tuple_t;
  using left_middle_t = nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t = nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t = nil_t;
  static constexpr long long int right_middle_idx = -1;

  using slast_t = nil_t;
  static constexpr long long int slast_idx = -1;

  using init_t =  empty_tuple_t;
  using last_t =  T;
  static constexpr long long int last_idx = 0;
};

template<typename T>
using cat_t<T> = typelist_t<T>;

template<typename T>
using cat_t<T,nil_t> = typelist_t<T>;

template<typename T>
using cat_t<nil_t,T> = typelist_t<T>;

template<typename T>
using cat_t<T,empty_tuple_t> = typelist_t<T>;

template<typename T>
using cat_t<empty_tuple_t,T> = typelist_t<T>;

template<typename T>
using cat_t<T,typelist_t<>> = typelist_t<T>;

template<typename T>
using cat_t<typelist_t<>,T> = typelist_t<T>;

template<typename T>
using cat_t<typelist_t<T>> = typelist_t<T>;

template<typename T>
using cat_t<typelist_t<typelist_t<T>>> = typelist_t<T>;

template<>
struct typelist_t<nil_t> : public empty_tuple_t  {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 0;}


  using tuple_t  =  empty_tuple_t;

  using head_t   =  nil_t;
  static constexpr long long int head_idx = -1;
  using tail_t   =  empty_tuple_t;

  using shead_t  =  nil_t;
  static constexpr long long int shead_idx = -1;

  using body_t   =  empty_tuple_t;
  using left_middle_t =  nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t =  nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t =  nil_t;
  static constexpr long long int right_middle_idx = -1;

  using slast_t  =  nil_t;
  static constexpr long long int slast_idx = -1;

  using init_t   =  empty_tuple_t;
  using last_t   =  nil_t;
  static constexpr long long int slat_idx = -1;
};

template<>
struct typelist_t<empty_tuple_t> : public empty_tuple_t  {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 0;}

  using tuple_t  =  empty_tuple_t;

  using head_t   =  nil_t;
  static constexpr long long int head_idx = -1;
  using tail_t   =  empty_tuple_t;

  using shead_t  =  nil_t;
  static constexpr long long int shead_idx = -1;

  using body_t   =  empty_tuple_t;
  using left_middle_t =  nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t =  nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t =  nil_t;
  static constexpr long long int right_middle_idx = -1;

  using slast_t  =  nil_t;
  static constexpr long long int slast_idx = -1;

  using init_t   =  empty_tuple_t;
  using last_t   =  nil_t;
  static constexpr long long int slat_idx = -1;
};

template<>
struct typelist_t<empty_tuple_t,empty_tuple_t> : public empty_tuple_t  {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 0;}

  using tuple_t  =  empty_tuple_t;

  using head_t   =  nil_t;
  static constexpr long long int head_idx = -1;
  using tail_t   =  empty_tuple_t;

  using shead_t  =  nil_t;
  static constexpr long long int shead_idx = -1;

  using body_t   =  empty_tuple_t;
  using left_middle_t =  nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t =  nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t =  nil_t;
  static constexpr long long int right_middle_idx = -1;

  using slast_t  =  nil_t;
  static constexpr long long int slast_idx = -1;

  using init_t   =  empty_tuple_t;
  using last_t   =  nil_t;
  static constexpr long long int slat_idx = -1;
};

template<>
struct typelist_t<empty_tuple_t,nil_t> : public empty_tuple_t  {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 0;}

  using tuple_t  =  empty_tuple_t;

  using head_t   =  nil_t;
  static constexpr long long int head_idx = -1;
  using tail_t   =  empty_tuple_t;

  using shead_t  =  nil_t;
  static constexpr long long int shead_idx = -1;

  using body_t   =  empty_tuple_t;
  using left_middle_t =  nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t =  nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t =  nil_t;
  static constexpr long long int right_middle_idx = -1;

  using slast_t  =  nil_t;
  static constexpr long long int slast_idx = -1;

  using init_t   =  empty_tuple_t;
  using last_t   =  nil_t;
  static constexpr long long int slat_idx = -1;
};

template<>
struct typelist_t<nil_t,empty_tuple_t> : public empty_tuple_t  {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 0;}

  using tuple_t  =  empty_tuple_t;

  using head_t   =  nil_t;
  static constexpr long long int head_idx = -1;
  using tail_t   =  empty_tuple_t;

  using shead_t  =  nil_t;
  static constexpr long long int shead_idx = -1;

  using body_t   =  empty_tuple_t;
  using left_middle_t =  nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t =  nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t =  nil_t;
  static constexpr long long int right_middle_idx = -1;

  using slast_t  =  nil_t;
  static constexpr long long int slast_idx = -1;

  using init_t   =  empty_tuple_t;
  using last_t   =  nil_t;
  static constexpr long long int slat_idx = -1;
};

template<>
struct typelist_t<nil_t,nil_t> : public empty_tuple_t  {
  using first_pack   = typelist_t<>;
  using last_pack    = typelist_t<>;
  static consteval std::size_t sz() noexcept {return 0;}

  using tuple_t  =  empty_tuple_t;

  using head_t   =  nil_t;
  static constexpr long long int head_idx = -1;
  using tail_t   =  empty_tuple_t;

  using shead_t  =  nil_t;
  static constexpr long long int shead_idx = -1;

  using body_t   =  empty_tuple_t;
  using left_middle_t =  nil_t;
  static constexpr long long int left_middle_idx = -1;
  using middle_t =  nil_t;
  static constexpr long long int middle_idx = -1;
  using right_middle_t =  nil_t;
  static constexpr long long int right_middle_idx = -1;

  using slast_t  =  nil_t;
  static constexpr long long int slast_idx = -1;

  using init_t   =  empty_tuple_t;
  using last_t   =  nil_t;
  static constexpr long long int slat_idx = -1;
};

} /// END OF TPLMP NAMESPACE
#endif // TPLMP_TYPELIST_T_HXX_INCLUDED
