#include "DS.h"
int min ;

Elm *insert_x ( Elm *p , int x )
{
        if ( p == NULL ) {
            struct Elm *k = malloc ( sizeof ( Elm ) ) ;
            k -> x = x ;
            k -> L = NULL ;
            k -> R = NULL ;
            k -> len = 1 ;
            k -> height = 1 ;
            p = k ;
            return k ;
        }
        if ( p -> x < x ) {
            p -> R = insert_x ( p -> R , x ) ;
            p -> len ++ ;
        }
        else {
            p -> L = insert_x ( p -> L , x ) ;
            p -> len ++ ;
        }
        p -> height = height_p ( p ) ;
        return p ;
}

Elm *search_x ( Elm *p , int x )
{
        if ( p == NULL ) {
            return NULL ;
        }
        if ( p -> x == x ) {
            return p ;
        }
        else
            if ( p -> x > x ) {
                return search_x ( p -> L , x ) ;
            }
            else {
                return search_x ( p -> R , x ) ;
            }
}

Elm *min_val ( Elm *p )
{
        Elm *temp = p ;
        while ( temp != NULL && temp -> L != NULL )
            temp = temp -> L ;
        return temp ;
}

Elm *delete_x ( Elm *p , int x )
{
        if ( p == NULL ) {
            return NULL ;
        }
        if ( p -> x > x ) {
            p -> L = delete_x ( p -> L , x ) ;
        }
        else
            if ( p -> x < x ) {
                p -> R = delete_x ( p -> R , x ) ;
            }
            else {
                if ( p -> L == NULL ) {
                    Elm *temp = p -> R ;
                    free ( p ) ;
                    return temp ;
                }
                else
                    if ( p -> R == NULL ) {
                        Elm *temp = p -> L ;
                        free ( p ) ;
                        return temp ;
                    }
                Elm *temp = min_val ( p -> R ) ;
                p -> x = temp -> x ;
                p -> R = delete_x ( p -> R , temp -> x ) ;
            }
        p -> len = size_p ( p ) ;
        p -> height = height_p ( p ) ;
        return p ;
}

Elm *delete_min ( Elm *p )
{
        if ( p -> L == NULL ) {
            min = p -> x ;
            return p -> R ;
        }
        p -> L = delete_min ( p -> L ) ;
        p -> len = size_p ( p ) ;
        return p ;
}

void in_order_p ( Elm *p )
{
        if ( p != NULL ) {
            in_order_p ( p -> L ) ;
            printf ( "%d %d %d\n" , p -> x , p -> len , p -> height ) ;
            in_order_p ( p -> R ) ;
        }
}

int rank_p ( Elm *p , int x )
{
        if ( p == NULL )
            return 0 ;
        if ( p -> x > x )
            return rank_p ( p -> L , x ) ;
        else
            if ( p -> x < x )
                return ( 1 + size_p ( p -> L ) + rank_p ( p -> R , x ) ) ;
            else
                return ( 1 + size_p ( p -> L ) ) ;
}

int size_p ( Elm *p )
{
        if ( p == NULL )
            return 0 ;
        else
            return ( size_p ( p -> L ) + size_p ( p -> R ) + 1 ) ;
}

Elm *floor_x ( Elm *p , int x )
{
        if ( p == NULL )
            return NULL ;
        if ( p -> x == x )
            return p ;
        if ( p -> x > x )
            return floor_x ( p -> L , x ) ;
        Elm *temp = floor_x ( p -> R , x ) ;
        if ( temp != NULL )
            return temp ;
        else
            return p ;
}

Elm *ceiling_x ( Elm *p , int x )
{
        if ( p == NULL )
            return NULL ;
        if ( p -> x == x )
            return p ;
        if ( p -> x < x )
            return ceiling_x ( p -> R , x ) ;
        Elm *temp = ceiling_x ( p -> L , x ) ;
        if ( temp != NULL )
            return temp ;
        else
            return p ;
}

int height_p ( Elm *p )
{
        if ( p == NULL )
            return 0 ;
        else {
            int L_depth = height_p ( p -> L ) ;
            int R_depth = height_p ( p -> R ) ;
            if ( L_depth > R_depth )
                return ( L_depth + 1 ) ;
            else
                return ( R_depth + 1 ) ;
        }
}

/*
  `ptree`-ийн зааж байгаа модонд `x` утгыг оруулна.
  Оруулахдаа хоёртын хайлтын модны зарчмаар оруулах бөгөөд оруулсан
  байрлалаас дээшхи өвөг эцгийн `len`, `height` утгууд өөрчлөгдөнө.
  Мод хоосон байсан бол `ptree->root` хаяг өөрчлөгдөж шинээр орсон оройг заана.
 */
void bs_put(BST *ptree, int x)
{
        ptree -> root = insert_x ( ptree -> root , x ) ;
}

/*
  `ptree`-ийн зааж байгаа модноос `x` утгыг хайн олдсон оройн `Elm*` хаягийг буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
  Мод дандаа ялгаатай элементүүд хадгална гэж үзэж болно.
 */
Elm *bs_get(const BST *ptree, int x)
{
        struct Elm *temp = search_x ( ptree -> root , x ) ;
        return temp ;
}

/*
  Устгах функц: ХХМноос `x` утгыг хайж олоод устгана.
  Олдохгүй бол юу ч хийхгүй.
 */
void bs_del(BST *ptree, int x)
{
        ptree -> root = delete_x ( ptree -> root , x ) ;
}

/*
  Хамгийн багыг устгах функц: ХХМноос хамгийг бага утгыг нь устгах функц.
  Устгасан утгыг буцаана.
 */
int bs_delMin(BST *ptree)
{
        ptree -> root = delete_min ( ptree -> root ) ;
        return min ;
}

/*
  ХХМыг inorder дарааллаар, нэг мөрөнд нэг утга хэвлэнэ.
 */
void bs_inorder(const BST *ptree)
{
        in_order_p ( ptree -> root ) ;
}

/*
  ХХМноос `x` утгаас эрс бага буюу тэнцүү байх хэдэн орой байгааг олж буцаана.
  Өөрөөр хэлбэл хоёртын хайлтын модны утгуудыг өсөх дарааллаар байрлуулбал
  `x`-ийг оролцуулаад өмнө хэдэн тоо байх вэ? гэсэн үг.
  `x` утга заавал модонд байх албагүй.
 */
int bs_rank(const BST *ptree, int x)
{
        return rank_p ( ptree -> root , x ) ;
}

/*
  ХХМноос `x` утгатай оройг хайж олоод, тухайн оройд суурилсан
  дэд модонд хэдэн орой байгааг олж буцаана.
  Олдохгүй бол -1-ийг буцаана.
 */
int bs_size(const BST *ptree, int x)
{
        Elm *temp = search_x ( ptree -> root , x ) ;
        if ( temp == NULL )
            return -1 ;
        else
            return size_p ( temp ) ;
}

/*
  XXMноос `x`-ээс бага буюу тэнцүү байх хамгийн их утгын `Elm *` хаягийг олж буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
 */
Elm *bs_floor(const BST *ptree, int x)
{
        Elm *temp = floor_x ( ptree -> root , x ) ;
        return temp ;
}

/*
  XXMноос `x`-ээс их буюу тэнцүү байх хамгийн бага утгын `Elm *` хаягийг олж буцаана.
  Олдохгүй бол `NULL` хаягийг буцаана.
 */
Elm *bs_ceiling(const BST *ptree, int x)
{
        Elm *temp = ceiling_x ( ptree -> root , x ) ;
        return temp ;
}

/*
  ХХМноос `x` утгатай оройг хайж олоод, тухайн оройд суурилсан
  дэд модны өндөр хэд байгааг олж буцаана. Олдохгүй бол -1-ийг буцаана.
 */
int bs_height(const BST *ptree, int x)
{
        Elm *temp = search_x ( ptree -> root , x ) ;
        if ( temp == NULL )
            return -1 ;
        return height_p ( temp ) ;
}
