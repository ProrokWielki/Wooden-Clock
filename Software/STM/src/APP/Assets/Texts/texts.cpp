#include <array>
#include <cassert>

#include "Minecart_8_0.hpp"
#include "Minecart_8_1.hpp"
#include "Minecart_8_2.hpp"
#include "Minecart_8_3.hpp"
#include "Minecart_8_4.hpp"
#include "Minecart_8_5.hpp"
#include "Minecart_8_6.hpp"
#include "Minecart_8_7.hpp"
#include "Minecart_8_8.hpp"
#include "Minecart_8_9.hpp"
#include "Minecart_8_colon.hpp"
#include "Minecart_8_degree.hpp"
#include "Minecart_8_dot.hpp"
#include "Minecart_8_lowercase_a.hpp"
#include "Minecart_8_lowercase_b.hpp"
#include "Minecart_8_lowercase_c.hpp"
#include "Minecart_8_lowercase_d.hpp"
#include "Minecart_8_lowercase_e.hpp"
#include "Minecart_8_lowercase_f.hpp"
#include "Minecart_8_lowercase_g.hpp"
#include "Minecart_8_lowercase_h.hpp"
#include "Minecart_8_lowercase_i.hpp"
#include "Minecart_8_lowercase_j.hpp"
#include "Minecart_8_lowercase_k.hpp"
#include "Minecart_8_lowercase_l.hpp"
#include "Minecart_8_lowercase_m.hpp"
#include "Minecart_8_lowercase_n.hpp"
#include "Minecart_8_lowercase_o.hpp"
#include "Minecart_8_lowercase_p.hpp"
#include "Minecart_8_lowercase_q.hpp"
#include "Minecart_8_lowercase_r.hpp"
#include "Minecart_8_lowercase_s.hpp"
#include "Minecart_8_lowercase_t.hpp"
#include "Minecart_8_lowercase_u.hpp"
#include "Minecart_8_lowercase_v.hpp"
#include "Minecart_8_lowercase_w.hpp"
#include "Minecart_8_lowercase_x.hpp"
#include "Minecart_8_lowercase_y.hpp"
#include "Minecart_8_lowercase_z.hpp"
#include "Minecart_8_percent.hpp"
#include "Minecart_8_space.hpp"
#include "Minecart_8_uppercase_A.hpp"
#include "Minecart_8_uppercase_B.hpp"
#include "Minecart_8_uppercase_C.hpp"
#include "Minecart_8_uppercase_D.hpp"
#include "Minecart_8_uppercase_E.hpp"
#include "Minecart_8_uppercase_F.hpp"
#include "Minecart_8_uppercase_G.hpp"
#include "Minecart_8_uppercase_H.hpp"
#include "Minecart_8_uppercase_I.hpp"
#include "Minecart_8_uppercase_J.hpp"
#include "Minecart_8_uppercase_K.hpp"
#include "Minecart_8_uppercase_L.hpp"
#include "Minecart_8_uppercase_M.hpp"
#include "Minecart_8_uppercase_N.hpp"
#include "Minecart_8_uppercase_O.hpp"
#include "Minecart_8_uppercase_P.hpp"
#include "Minecart_8_uppercase_Q.hpp"
#include "Minecart_8_uppercase_R.hpp"
#include "Minecart_8_uppercase_S.hpp"
#include "Minecart_8_uppercase_T.hpp"
#include "Minecart_8_uppercase_U.hpp"
#include "Minecart_8_uppercase_V.hpp"
#include "Minecart_8_uppercase_W.hpp"
#include "Minecart_8_uppercase_X.hpp"
#include "Minecart_8_uppercase_Y.hpp"
#include "Minecart_8_uppercase_Z.hpp"

#include <widgets/Image.hpp>

Image * TextFactory::to_image(char character)
{
    static Image Minecart_8_space_Image{Minecart_8_space::WIDTH, Minecart_8_space::HEIGHT, Minecart_8_space::DATA.data()};
    static Image Minecart_8_dot_Image{Minecart_8_dot::WIDTH, Minecart_8_dot::HEIGHT, Minecart_8_dot::DATA.data()};
    static Image Minecart_8_colon_Image{Minecart_8_colon::WIDTH, Minecart_8_colon::HEIGHT, Minecart_8_colon::DATA.data()};
    static Image Minecart_8_degree_Image{Minecart_8_degree::WIDTH, Minecart_8_degree::HEIGHT, Minecart_8_degree::DATA.data()};
    static Image Minecart_8_percent_Image{Minecart_8_percent::WIDTH, Minecart_8_percent::HEIGHT, Minecart_8_percent::DATA.data()};
    static Image Minecart_8_uppercase_A_Image{Minecart_8_uppercase_A::WIDTH, Minecart_8_uppercase_A::HEIGHT, Minecart_8_uppercase_A::DATA.data()};
    static Image Minecart_8_uppercase_B_Image{Minecart_8_uppercase_B::WIDTH, Minecart_8_uppercase_B::HEIGHT, Minecart_8_uppercase_B::DATA.data()};
    static Image Minecart_8_uppercase_C_Image{Minecart_8_uppercase_C::WIDTH, Minecart_8_uppercase_C::HEIGHT, Minecart_8_uppercase_C::DATA.data()};
    static Image Minecart_8_uppercase_D_Image{Minecart_8_uppercase_D::WIDTH, Minecart_8_uppercase_D::HEIGHT, Minecart_8_uppercase_D::DATA.data()};
    static Image Minecart_8_uppercase_E_Image{Minecart_8_uppercase_E::WIDTH, Minecart_8_uppercase_E::HEIGHT, Minecart_8_uppercase_E::DATA.data()};
    static Image Minecart_8_uppercase_F_Image{Minecart_8_uppercase_F::WIDTH, Minecart_8_uppercase_F::HEIGHT, Minecart_8_uppercase_F::DATA.data()};
    static Image Minecart_8_uppercase_G_Image{Minecart_8_uppercase_G::WIDTH, Minecart_8_uppercase_G::HEIGHT, Minecart_8_uppercase_G::DATA.data()};
    static Image Minecart_8_uppercase_H_Image{Minecart_8_uppercase_H::WIDTH, Minecart_8_uppercase_H::HEIGHT, Minecart_8_uppercase_H::DATA.data()};
    static Image Minecart_8_uppercase_I_Image{Minecart_8_uppercase_I::WIDTH, Minecart_8_uppercase_I::HEIGHT, Minecart_8_uppercase_I::DATA.data()};
    static Image Minecart_8_uppercase_J_Image{Minecart_8_uppercase_J::WIDTH, Minecart_8_uppercase_J::HEIGHT, Minecart_8_uppercase_J::DATA.data()};
    static Image Minecart_8_uppercase_K_Image{Minecart_8_uppercase_K::WIDTH, Minecart_8_uppercase_K::HEIGHT, Minecart_8_uppercase_K::DATA.data()};
    static Image Minecart_8_uppercase_L_Image{Minecart_8_uppercase_L::WIDTH, Minecart_8_uppercase_L::HEIGHT, Minecart_8_uppercase_L::DATA.data()};
    static Image Minecart_8_uppercase_M_Image{Minecart_8_uppercase_M::WIDTH, Minecart_8_uppercase_M::HEIGHT, Minecart_8_uppercase_M::DATA.data()};
    static Image Minecart_8_uppercase_N_Image{Minecart_8_uppercase_N::WIDTH, Minecart_8_uppercase_N::HEIGHT, Minecart_8_uppercase_N::DATA.data()};
    static Image Minecart_8_uppercase_O_Image{Minecart_8_uppercase_O::WIDTH, Minecart_8_uppercase_O::HEIGHT, Minecart_8_uppercase_O::DATA.data()};
    static Image Minecart_8_uppercase_P_Image{Minecart_8_uppercase_P::WIDTH, Minecart_8_uppercase_P::HEIGHT, Minecart_8_uppercase_P::DATA.data()};
    static Image Minecart_8_uppercase_Q_Image{Minecart_8_uppercase_Q::WIDTH, Minecart_8_uppercase_Q::HEIGHT, Minecart_8_uppercase_Q::DATA.data()};
    static Image Minecart_8_uppercase_R_Image{Minecart_8_uppercase_R::WIDTH, Minecart_8_uppercase_R::HEIGHT, Minecart_8_uppercase_R::DATA.data()};
    static Image Minecart_8_uppercase_S_Image{Minecart_8_uppercase_S::WIDTH, Minecart_8_uppercase_S::HEIGHT, Minecart_8_uppercase_S::DATA.data()};
    static Image Minecart_8_uppercase_T_Image{Minecart_8_uppercase_T::WIDTH, Minecart_8_uppercase_T::HEIGHT, Minecart_8_uppercase_T::DATA.data()};
    static Image Minecart_8_uppercase_U_Image{Minecart_8_uppercase_U::WIDTH, Minecart_8_uppercase_U::HEIGHT, Minecart_8_uppercase_U::DATA.data()};
    static Image Minecart_8_uppercase_V_Image{Minecart_8_uppercase_V::WIDTH, Minecart_8_uppercase_V::HEIGHT, Minecart_8_uppercase_V::DATA.data()};
    static Image Minecart_8_uppercase_W_Image{Minecart_8_uppercase_W::WIDTH, Minecart_8_uppercase_W::HEIGHT, Minecart_8_uppercase_W::DATA.data()};
    static Image Minecart_8_uppercase_X_Image{Minecart_8_uppercase_X::WIDTH, Minecart_8_uppercase_X::HEIGHT, Minecart_8_uppercase_X::DATA.data()};
    static Image Minecart_8_uppercase_Y_Image{Minecart_8_uppercase_Y::WIDTH, Minecart_8_uppercase_Y::HEIGHT, Minecart_8_uppercase_Y::DATA.data()};
    static Image Minecart_8_uppercase_Z_Image{Minecart_8_uppercase_Z::WIDTH, Minecart_8_uppercase_Z::HEIGHT, Minecart_8_uppercase_Z::DATA.data()};
    static Image Minecart_8_lowercase_a_Image{Minecart_8_lowercase_a::WIDTH, Minecart_8_lowercase_a::HEIGHT, Minecart_8_lowercase_a::DATA.data()};
    static Image Minecart_8_lowercase_b_Image{Minecart_8_lowercase_b::WIDTH, Minecart_8_lowercase_b::HEIGHT, Minecart_8_lowercase_b::DATA.data()};
    static Image Minecart_8_lowercase_c_Image{Minecart_8_lowercase_c::WIDTH, Minecart_8_lowercase_c::HEIGHT, Minecart_8_lowercase_c::DATA.data()};
    static Image Minecart_8_lowercase_d_Image{Minecart_8_lowercase_d::WIDTH, Minecart_8_lowercase_d::HEIGHT, Minecart_8_lowercase_d::DATA.data()};
    static Image Minecart_8_lowercase_e_Image{Minecart_8_lowercase_e::WIDTH, Minecart_8_lowercase_e::HEIGHT, Minecart_8_lowercase_e::DATA.data()};
    static Image Minecart_8_lowercase_f_Image{Minecart_8_lowercase_f::WIDTH, Minecart_8_lowercase_f::HEIGHT, Minecart_8_lowercase_f::DATA.data()};
    static Image Minecart_8_lowercase_g_Image{Minecart_8_lowercase_g::WIDTH, Minecart_8_lowercase_g::HEIGHT, Minecart_8_lowercase_g::DATA.data()};
    static Image Minecart_8_lowercase_h_Image{Minecart_8_lowercase_h::WIDTH, Minecart_8_lowercase_h::HEIGHT, Minecart_8_lowercase_h::DATA.data()};
    static Image Minecart_8_lowercase_i_Image{Minecart_8_lowercase_i::WIDTH, Minecart_8_lowercase_i::HEIGHT, Minecart_8_lowercase_i::DATA.data()};
    static Image Minecart_8_lowercase_j_Image{Minecart_8_lowercase_j::WIDTH, Minecart_8_lowercase_j::HEIGHT, Minecart_8_lowercase_j::DATA.data()};
    static Image Minecart_8_lowercase_k_Image{Minecart_8_lowercase_k::WIDTH, Minecart_8_lowercase_k::HEIGHT, Minecart_8_lowercase_k::DATA.data()};
    static Image Minecart_8_lowercase_l_Image{Minecart_8_lowercase_l::WIDTH, Minecart_8_lowercase_l::HEIGHT, Minecart_8_lowercase_l::DATA.data()};
    static Image Minecart_8_lowercase_m_Image{Minecart_8_lowercase_m::WIDTH, Minecart_8_lowercase_m::HEIGHT, Minecart_8_lowercase_m::DATA.data()};
    static Image Minecart_8_lowercase_n_Image{Minecart_8_lowercase_n::WIDTH, Minecart_8_lowercase_n::HEIGHT, Minecart_8_lowercase_n::DATA.data()};
    static Image Minecart_8_lowercase_o_Image{Minecart_8_lowercase_o::WIDTH, Minecart_8_lowercase_o::HEIGHT, Minecart_8_lowercase_o::DATA.data()};
    static Image Minecart_8_lowercase_p_Image{Minecart_8_lowercase_p::WIDTH, Minecart_8_lowercase_p::HEIGHT, Minecart_8_lowercase_p::DATA.data()};
    static Image Minecart_8_lowercase_q_Image{Minecart_8_lowercase_q::WIDTH, Minecart_8_lowercase_q::HEIGHT, Minecart_8_lowercase_q::DATA.data()};
    static Image Minecart_8_lowercase_r_Image{Minecart_8_lowercase_r::WIDTH, Minecart_8_lowercase_r::HEIGHT, Minecart_8_lowercase_r::DATA.data()};
    static Image Minecart_8_lowercase_s_Image{Minecart_8_lowercase_s::WIDTH, Minecart_8_lowercase_s::HEIGHT, Minecart_8_lowercase_s::DATA.data()};
    static Image Minecart_8_lowercase_t_Image{Minecart_8_lowercase_t::WIDTH, Minecart_8_lowercase_t::HEIGHT, Minecart_8_lowercase_t::DATA.data()};
    static Image Minecart_8_lowercase_u_Image{Minecart_8_lowercase_u::WIDTH, Minecart_8_lowercase_u::HEIGHT, Minecart_8_lowercase_u::DATA.data()};
    static Image Minecart_8_lowercase_v_Image{Minecart_8_lowercase_v::WIDTH, Minecart_8_lowercase_v::HEIGHT, Minecart_8_lowercase_v::DATA.data()};
    static Image Minecart_8_lowercase_w_Image{Minecart_8_lowercase_w::WIDTH, Minecart_8_lowercase_w::HEIGHT, Minecart_8_lowercase_w::DATA.data()};
    static Image Minecart_8_lowercase_x_Image{Minecart_8_lowercase_x::WIDTH, Minecart_8_lowercase_x::HEIGHT, Minecart_8_lowercase_x::DATA.data()};
    static Image Minecart_8_lowercase_y_Image{Minecart_8_lowercase_y::WIDTH, Minecart_8_lowercase_y::HEIGHT, Minecart_8_lowercase_y::DATA.data()};
    static Image Minecart_8_lowercase_z_Image{Minecart_8_lowercase_z::WIDTH, Minecart_8_lowercase_z::HEIGHT, Minecart_8_lowercase_z::DATA.data()};
    static Image Minecart_8_0_Image{Minecart_8_0::WIDTH, Minecart_8_0::HEIGHT, Minecart_8_0::DATA.data()};
    static Image Minecart_8_1_Image{Minecart_8_1::WIDTH, Minecart_8_1::HEIGHT, Minecart_8_1::DATA.data()};
    static Image Minecart_8_2_Image{Minecart_8_2::WIDTH, Minecart_8_2::HEIGHT, Minecart_8_2::DATA.data()};
    static Image Minecart_8_3_Image{Minecart_8_3::WIDTH, Minecart_8_3::HEIGHT, Minecart_8_3::DATA.data()};
    static Image Minecart_8_4_Image{Minecart_8_4::WIDTH, Minecart_8_4 ::HEIGHT, Minecart_8_4::DATA.data()};
    static Image Minecart_8_5_Image{Minecart_8_5::WIDTH, Minecart_8_5::HEIGHT, Minecart_8_5::DATA.data()};
    static Image Minecart_8_6_Image{Minecart_8_6::WIDTH, Minecart_8_6::HEIGHT, Minecart_8_6::DATA.data()};
    static Image Minecart_8_7_Image{Minecart_8_7::WIDTH, Minecart_8_7::HEIGHT, Minecart_8_7::DATA.data()};
    static Image Minecart_8_8_Image{Minecart_8_8::WIDTH, Minecart_8_8::HEIGHT, Minecart_8_8::DATA.data()};
    static Image Minecart_8_9_Image{Minecart_8_9::WIDTH, Minecart_8_9::HEIGHT, Minecart_8_9::DATA.data()};

    switch (character)
    {
        case ' ':
            return &Minecart_8_space_Image;
        case ':':
            return &Minecart_8_colon_Image;
        case '.':
            return &Minecart_8_dot_Image;
        case '*':
            return &Minecart_8_degree_Image;
        case '%':
            return &Minecart_8_percent_Image;
        case 'A':
            return &Minecart_8_uppercase_A_Image;
        case 'B':
            return &Minecart_8_uppercase_B_Image;
        case 'C':
            return &Minecart_8_uppercase_C_Image;
        case 'D':
            return &Minecart_8_uppercase_D_Image;
        case 'E':
            return &Minecart_8_uppercase_E_Image;
        case 'F':
            return &Minecart_8_uppercase_F_Image;
        case 'G':
            return &Minecart_8_uppercase_G_Image;
        case 'H':
            return &Minecart_8_uppercase_H_Image;
        case 'I':
            return &Minecart_8_uppercase_I_Image;
        case 'J':
            return &Minecart_8_uppercase_J_Image;
        case 'K':
            return &Minecart_8_uppercase_K_Image;
        case 'L':
            return &Minecart_8_uppercase_L_Image;
        case 'M':
            return &Minecart_8_uppercase_M_Image;
        case 'N':
            return &Minecart_8_uppercase_N_Image;
        case 'O':
            return &Minecart_8_uppercase_O_Image;
        case 'P':
            return &Minecart_8_uppercase_P_Image;
        case 'Q':
            return &Minecart_8_uppercase_Q_Image;
        case 'R':
            return &Minecart_8_uppercase_R_Image;
        case 'S':
            return &Minecart_8_uppercase_S_Image;
        case 'T':
            return &Minecart_8_uppercase_T_Image;
        case 'U':
            return &Minecart_8_uppercase_U_Image;
        case 'V':
            return &Minecart_8_uppercase_V_Image;
        case 'W':
            return &Minecart_8_uppercase_W_Image;
        case 'X':
            return &Minecart_8_uppercase_X_Image;
        case 'Y':
            return &Minecart_8_uppercase_Y_Image;
        case 'Z':
            return &Minecart_8_uppercase_Z_Image;
        case 'a':
            return &Minecart_8_lowercase_a_Image;
        case 'b':
            return &Minecart_8_lowercase_b_Image;
        case 'c':
            return &Minecart_8_lowercase_c_Image;
        case 'd':
            return &Minecart_8_lowercase_d_Image;
        case 'e':
            return &Minecart_8_lowercase_e_Image;
        case 'f':
            return &Minecart_8_lowercase_f_Image;
        case 'g':
            return &Minecart_8_lowercase_g_Image;
        case 'h':
            return &Minecart_8_lowercase_h_Image;
        case 'i':
            return &Minecart_8_lowercase_i_Image;
        case 'j':
            return &Minecart_8_lowercase_j_Image;
        case 'k':
            return &Minecart_8_lowercase_k_Image;
        case 'l':
            return &Minecart_8_lowercase_l_Image;
        case 'm':
            return &Minecart_8_lowercase_m_Image;
        case 'n':
            return &Minecart_8_lowercase_n_Image;
        case 'o':
            return &Minecart_8_lowercase_o_Image;
        case 'p':
            return &Minecart_8_lowercase_p_Image;
        case 'q':
            return &Minecart_8_lowercase_q_Image;
        case 'r':
            return &Minecart_8_lowercase_r_Image;
        case 's':
            return &Minecart_8_lowercase_s_Image;
        case 't':
            return &Minecart_8_lowercase_t_Image;
        case 'u':
            return &Minecart_8_lowercase_u_Image;
        case 'v':
            return &Minecart_8_lowercase_v_Image;
        case 'w':
            return &Minecart_8_lowercase_w_Image;
        case 'x':
            return &Minecart_8_lowercase_x_Image;
        case 'y':
            return &Minecart_8_lowercase_y_Image;
        case 'z':
            return &Minecart_8_lowercase_z_Image;
        case '0':
            return &Minecart_8_0_Image;
        case '1':
            return &Minecart_8_1_Image;
        case '2':
            return &Minecart_8_2_Image;
        case '3':
            return &Minecart_8_3_Image;
        case '4':
            return &Minecart_8_4_Image;
        case '5':
            return &Minecart_8_5_Image;
        case '6':
            return &Minecart_8_6_Image;
        case '7':
            return &Minecart_8_7_Image;
        case '8':
            return &Minecart_8_8_Image;
        case '9':
            return &Minecart_8_9_Image;
        default:
            assert(false && "Character not supported");
            return nullptr;
    }
}

uint8_t TextFactory::font_height()
{
    constexpr uint8_t FONT_HEIGHT{11};
    return FONT_HEIGHT;
}
