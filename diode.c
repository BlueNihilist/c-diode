#include <stddef.h>
#include "diode.h"
#include "list.h"

int dframe_to_bits(struct dframe fr, unsigned char *buf) {
        size_t ind = 0;
        size_t count = 0;

        for (size_t i = 0; i < fr.len; i++) {
                // !! to make sure fr.arr[i].state is either 0 or 1
                buf[ind] |= !!(fr.arr[i].state);
                buf[ind] = buf[ind] << 1;
                count++;
                if (count % 8 == 0) {
                        ind++;
                }
        } 
        
        return 0;
}

// to_animation() allocates its own memory to store states from **array 
struct animation to_animation(unsigned char **array, size_t n_frames,
                                size_t n_diodes, unsigned int fps, 
                                unsigned int ani_mode, unsigned int repetitions) 
{
        struct animation animation = { 0 };
        struct lnode *ani_start = NULL;

        for (size_t f_ind = 0; f_ind < n_frames; f_ind++) {
                struct dframe *frame = (struct dframe *) malloc(sizeof(struct dframe));
                struct lnode *frame_lnode = (struct lnode*) malloc(sizeof(struct lnode));
                frame->arr = (struct dstate*) malloc(sizeof(struct dstate) * n_diodes);
                frame->len = n_diodes;
                for (size_t d_ind = 0; d_ind < n_diodes; d_ind++) {
                        frame->arr[d_ind].state = array[f_ind][d_ind];
                        frame->arr[d_ind].mode = DIODE_PHY;
                        frame_lnode->data = frame;
                        frame_lnode->next = NULL;
                }
                if (!animation.head) {
                        animation.head = frame_lnode;
                        ani_start = frame_lnode;
                } else {
                        animation.head->next = frame_lnode;
                        animation.head = frame_lnode;
                }       
        }

        if (ani_mode == ANI_REPEAT) {
                // connect last frame to the first to make a loop
                animation.head->next = ani_start; 
                animation.head = ani_start;
        }

        animation.fps = fps;
        animation.ani_mode = ani_mode;
        animation.repeats = repetitions;

        return animation;
}
