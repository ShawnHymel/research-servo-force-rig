
#include "header.h"

const unsigned char is_categorical[] = {  0, 0, 0, 0, 0, 0, };
static const int32_t num_class[] = {  1, };

int32_t get_num_target(void) {
  return N_TARGET;
}
void get_num_class(int32_t* out) {
  for (int i = 0; i < N_TARGET; ++i) {
    out[i] = num_class[i];
  }
}
int32_t get_num_feature(void) {
  return 6;
}
const char* get_threshold_type(void) {
  return "float32";
}
const char* get_leaf_output_type(void) {
  return "float32";
}

void predict(union Entry* data, int pred_margin, float* result) {
  
  // Quantize data
  for (int i = 0; i < 6; ++i) {
    if (data[i].missing != -1 && !is_categorical[i]) {
      data[i].qvalue = quantize(data[i].fvalue, i);
    }
  }
  
  unsigned int tmp;
  if ( (data[2].missing != -1) && (data[2].qvalue < 18)) {
    if ( (data[2].missing != -1) && (data[2].qvalue < 6)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 20)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 54)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 16)) {
            result[0] += -0.14676324;
          } else {
            result[0] += -0.113004185;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 42)) {
            result[0] += -0.055997252;
          } else {
            result[0] += 0.091722;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 30)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 22)) {
            result[0] += -0.038559794;
          } else {
            result[0] += -0.14878531;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 42)) {
            result[0] += 0.005938812;
          } else {
            result[0] += -0.1482353;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
        if ( (data[3].missing != -1) && (data[3].qvalue < 2)) {
          result[0] += -0.14895105;
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 24)) {
            result[0] += -0.037144583;
          } else {
            result[0] += 0.09860902;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 34)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 32)) {
            result[0] += -0.14934859;
          } else {
            result[0] += -0.09562855;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 28)) {
            result[0] += -0.06869797;
          } else {
            result[0] += 0.08504081;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 26)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 32)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 20)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
            result[0] += -0.14895834;
          } else {
            result[0] += 0.11524689;
          }
        } else {
          result[0] += -0.14928198;
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 44)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 0)) {
            result[0] += -0.14347827;
          } else {
            result[0] += 0.14241743;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 18)) {
            result[0] += -0.1292692;
          } else {
            result[0] += -0.044782273;
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 34)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 36)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 26)) {
            result[0] += -0.123470895;
          } else {
            result[0] += 0.019196017;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 62)) {
            result[0] += 0.02906864;
          } else {
            result[0] += -0.13342509;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
          result[0] += -0.14117648;
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 42)) {
            result[0] += 0.07840392;
          } else {
            result[0] += 0.13785869;
          }
        }
      }
    }
  }
  if ( (data[4].missing != -1) && (data[4].qvalue < 26)) {
    if ( (data[0].missing != -1) && (data[0].qvalue < 26)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 12)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 14)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 6)) {
            result[0] += -0.10496067;
          } else {
            result[0] += -0.10071058;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 26)) {
            result[0] += -0.08636345;
          } else {
            result[0] += -0.010489209;
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 2)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 12)) {
            result[0] += -0.10544137;
          } else {
            result[0] += -0.043519307;
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 12)) {
            result[0] += -0.09589892;
          } else {
            result[0] += -0.04777885;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 40)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 26)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 2)) {
            result[0] += -0.11473814;
          } else {
            result[0] += 0.07231081;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 28)) {
            result[0] += -0.054722264;
          } else {
            result[0] += -0.10419035;
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 20)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 0)) {
            result[0] += -0.10531322;
          } else {
            result[0] += 0.08846767;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 22)) {
            result[0] += -0.102639;
          } else {
            result[0] += 0.08833059;
          }
        }
      }
    }
  } else {
    if ( (data[2].missing != -1) && (data[2].qvalue < 18)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 42)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 16)) {
            result[0] += -0.039567564;
          } else {
            result[0] += 0.12183535;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 48)) {
            result[0] += -0.11858526;
          } else {
            result[0] += -0.10454873;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
            result[0] += 0.1369721;
          } else {
            result[0] += -0.10065603;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
            result[0] += -0.008706102;
          } else {
            result[0] += -0.11746317;
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 38)) {
        if ( (data[0].missing != -1) && (data[0].qvalue < 8)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 44)) {
            result[0] += -0.07748246;
          } else {
            result[0] += 0.060895637;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 32)) {
            result[0] += 0.036084604;
          } else {
            result[0] += -0.098465495;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
          result[0] += -0.10131489;
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 40)) {
            result[0] += 0.09668063;
          } else {
            result[0] += 0.053347714;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 20)) {
    if ( (data[2].missing != -1) && (data[2].qvalue < 8)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 16)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 52)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 24)) {
            result[0] += -0.07229851;
          } else {
            result[0] += -0.049693875;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
            result[0] += 0.057419494;
          } else {
            result[0] += -0.03366981;
          }
        }
      } else {
        if ( (data[2].missing != -1) && (data[2].qvalue < 2)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 0)) {
            result[0] += -0.109389454;
          } else {
            result[0] += -0.07313529;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 32)) {
            result[0] += -0.053980857;
          } else {
            result[0] += -0.0069511137;
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 50)) {
        if ( (data[3].missing != -1) && (data[3].qvalue < 18)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 0)) {
            result[0] += -0.04774181;
          } else {
            result[0] += 0.029561501;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 34)) {
            result[0] += -0.07320508;
          } else {
            result[0] += -0.008692507;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 26)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 16)) {
            result[0] += 0.0491158;
          } else {
            result[0] += -0.07230565;
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 22)) {
            result[0] += 0.09132561;
          } else {
            result[0] += -0.10296646;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 28)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 32)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
            result[0] += -0.07453163;
          } else {
            result[0] += 0.0680095;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 26)) {
            result[0] += -0.07536587;
          } else {
            result[0] += -0.10979808;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 0)) {
            result[0] += -0.07271022;
          } else {
            result[0] += 0.077592194;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 54)) {
            result[0] += -0.0075496985;
          } else {
            result[0] += -0.088943966;
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 40)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 42)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 20)) {
            result[0] += 0.039769858;
          } else {
            result[0] += -0.06257269;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 62)) {
            result[0] += 0.029877068;
          } else {
            result[0] += -0.07356167;
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 56)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 40)) {
            result[0] += 0.063230634;
          } else {
            result[0] += -0.1382272;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
            result[0] += -0.06759602;
          } else {
            result[0] += 0.069944054;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 16)) {
    if ( (data[0].missing != -1) && (data[0].qvalue < 22)) {
      if ( (data[4].missing != -1) && (data[4].qvalue < 30)) {
        if ( (data[0].missing != -1) && (data[0].qvalue < 6)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 10)) {
            result[0] += -0.051821537;
          } else {
            result[0] += -0.046437606;
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 12)) {
            result[0] += -0.046914086;
          } else {
            result[0] += -0.012127265;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 42)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
            result[0] += 0.014399356;
          } else {
            result[0] += -0.0700819;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 24)) {
            result[0] += 0.09427081;
          } else {
            result[0] += -0.014948552;
          }
        }
      }
    } else {
      if ( (data[3].missing != -1) && (data[3].qvalue < 30)) {
        if ( (data[3].missing != -1) && (data[3].qvalue < 22)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 4)) {
            result[0] += -0.07209269;
          } else {
            result[0] += 0.04458931;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 14)) {
            result[0] += 0.089560516;
          } else {
            result[0] += -0.055373877;
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 16)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 30)) {
            result[0] += -0.0091155;
          } else {
            result[0] += 0.059341498;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 50)) {
            result[0] += -0.078017175;
          } else {
            result[0] += 0.0013950538;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 28)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 32)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 8)) {
            result[0] += -0.039901868;
          } else {
            result[0] += 0.061976314;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 26)) {
            result[0] += -0.052649323;
          } else {
            result[0] += -0.07741695;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 44)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 0)) {
            result[0] += -0.053843196;
          } else {
            result[0] += 0.05514963;
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 18)) {
            result[0] += 0.008463748;
          } else {
            result[0] += -0.055663858;
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 32)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 44)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 22)) {
            result[0] += 0.029884642;
          } else {
            result[0] += -0.08894926;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
            result[0] += 0.031218238;
          } else {
            result[0] += -0.1306187;
          }
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 46)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 34)) {
            result[0] += 0.028332815;
          } else {
            result[0] += -0.09538542;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 48)) {
            result[0] += 0.04512032;
          } else {
            result[0] += 0.05232172;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 20)) {
    if ( (data[2].missing != -1) && (data[2].qvalue < 10)) {
      if ( (data[0].missing != -1) && (data[0].qvalue < 24)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 30)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 2)) {
            result[0] += -0.036717415;
          } else {
            result[0] += -0.033560727;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
            result[0] += -0.11064788;
          } else {
            result[0] += -0.0072475285;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 28)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 22)) {
            result[0] += -0.00062586414;
          } else {
            result[0] += -0.040142573;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 40)) {
            result[0] += 0.049310964;
          } else {
            result[0] += -0.036611866;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 40)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 10)) {
            result[0] += -0.026119752;
          } else {
            result[0] += 0.023195127;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 48)) {
            result[0] += -0.03534685;
          } else {
            result[0] += -0.051522836;
          }
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 46)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 14)) {
            result[0] += -0.0018321251;
          } else {
            result[0] += -0.08796387;
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 22)) {
            result[0] += 0.05787839;
          } else {
            result[0] += -0.070899315;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 30)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 32)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
            result[0] += -0.045894288;
          } else {
            result[0] += 0.037097063;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 28)) {
            result[0] += -0.03784011;
          } else {
            result[0] += -0.095920496;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 0)) {
            result[0] += -0.037758205;
          } else {
            result[0] += 0.039324127;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 54)) {
            result[0] += 0.013964127;
          } else {
            result[0] += -0.056697927;
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 44)) {
        if ( (data[2].missing != -1) && (data[2].qvalue < 34)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 44)) {
            result[0] += -0.0029253452;
          } else {
            result[0] += 0.022542847;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 50)) {
            result[0] += -0.08957967;
          } else {
            result[0] += -0.005037086;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 50)) {
            result[0] += 0.032052834;
          } else {
            result[0] += 0.037296485;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
            result[0] += 0.013946206;
          } else {
            result[0] += -0.11731868;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 14)) {
    if ( (data[0].missing != -1) && (data[0].qvalue < 16)) {
      if ( (data[4].missing != -1) && (data[4].qvalue < 46)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 12)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 6)) {
            result[0] += -0.024982749;
          } else {
            result[0] += -0.046420045;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 20)) {
            result[0] += -0.007861002;
          } else {
            result[0] += -0.024875192;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 42)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
            result[0] += 0.038142554;
          } else {
            result[0] += -0.05407499;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 56)) {
            result[0] += 0.07414671;
          } else {
            result[0] += -0.08024226;
          }
        }
      }
    } else {
      if ( (data[3].missing != -1) && (data[3].qvalue < 22)) {
        if ( (data[3].missing != -1) && (data[3].qvalue < 12)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 2)) {
            result[0] += -0.04868307;
          } else {
            result[0] += -0.008068323;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 18)) {
            result[0] += 0.003547243;
          } else {
            result[0] += 0.0398712;
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 6)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 8)) {
            result[0] += -0.032365922;
          } else {
            result[0] += -0.02392044;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 10)) {
            result[0] += 0.010594298;
          } else {
            result[0] += -0.016838895;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 32)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 44)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 6)) {
            result[0] += -0.023243772;
          } else {
            result[0] += 0.03357937;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 28)) {
            result[0] += -0.026202828;
          } else {
            result[0] += -0.077724285;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 22)) {
            result[0] += 0.027704882;
          } else {
            result[0] += -0.059350606;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 26)) {
            result[0] += -0.011334278;
          } else {
            result[0] += -0.07622829;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 44)) {
          result[0] += -0.12068205;
        } else {
          result[0] += -0.07480841;
        }
      } else {
        if ( (data[0].missing != -1) && (data[0].qvalue < 48)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 38)) {
            result[0] += 0.011086283;
          } else {
            result[0] += -0.056552798;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
            result[0] += 0.027232016;
          } else {
            result[0] += 0.021664154;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 22)) {
    if ( (data[0].missing != -1) && (data[0].qvalue < 30)) {
      if ( (data[4].missing != -1) && (data[4].qvalue < 40)) {
        if ( (data[0].missing != -1) && (data[0].qvalue < 10)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 8)) {
            result[0] += -0.018087033;
          } else {
            result[0] += -0.015983982;
          }
        } else {
          if ( (data[1].missing != -1) && (data[1].qvalue < 2)) {
            result[0] += -0.0036648232;
          } else {
            result[0] += -0.016907442;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 52)) {
            result[0] += -0.06632492;
          } else {
            result[0] += -0.1262366;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
            result[0] += 0.032849282;
          } else {
            result[0] += -0.008142266;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 38)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 26)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 10)) {
            result[0] += -0.022413628;
          } else {
            result[0] += 0.02916266;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 14)) {
            result[0] += -0.13434249;
          } else {
            result[0] += -0.018656757;
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 20)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 4)) {
            result[0] += -0.031609777;
          } else {
            result[0] += 0.03104664;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 16)) {
            result[0] += -0.044229656;
          } else {
            result[0] += 0.019499088;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 32)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 44)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
            result[0] += -0.02556103;
          } else {
            result[0] += 0.019203184;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 26)) {
            result[0] += -0.017900128;
          } else {
            result[0] += -0.0513665;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 4)) {
            result[0] += 0.055528216;
          } else {
            result[0] += 0.016425345;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 28)) {
            result[0] += -0.0066476585;
          } else {
            result[0] += -0.059192006;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 44)) {
            result[0] += -0.09117458;
          } else {
            result[0] += -0.050975222;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 52)) {
            result[0] += 0.013640233;
          } else {
            result[0] += 0.018569175;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 38)) {
            result[0] += -0.16099788;
          } else {
            result[0] += 0.01794375;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 54)) {
            result[0] += -0.11530972;
          } else {
            result[0] += 0.0677711;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 22)) {
    if ( (data[0].missing != -1) && (data[0].qvalue < 36)) {
      if ( (data[4].missing != -1) && (data[4].qvalue < 46)) {
        if ( (data[1].missing != -1) && (data[1].qvalue < 10)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 52)) {
            result[0] += -0.012509849;
          } else {
            result[0] += 0.07056863;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 18)) {
            result[0] += 0.13207816;
          } else {
            result[0] += -0.009859836;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 52)) {
            result[0] += -0.051716417;
          } else {
            result[0] += -0.09059333;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
            result[0] += 0.0069473344;
          } else {
            result[0] += -0.05828621;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 36)) {
        if ( (data[1].missing != -1) && (data[1].qvalue < 2)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 2)) {
            result[0] += -0.02369283;
          } else {
            result[0] += 0.013635618;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 0)) {
            result[0] += -0.04345499;
          } else {
            result[0] += -0.012633191;
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 20)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 4)) {
            result[0] += -0.032037318;
          } else {
            result[0] += 0.026801065;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 20)) {
            result[0] += -0.030953126;
          } else {
            result[0] += 0.022547318;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 34)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 44)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 10)) {
            result[0] += -0.010280265;
          } else {
            result[0] += 0.018055454;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 30)) {
            result[0] += -0.014434149;
          } else {
            result[0] += -0.08507943;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 0)) {
            result[0] += -0.04193952;
          } else {
            result[0] += 0.013890632;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 54)) {
            result[0] += 0.017349634;
          } else {
            result[0] += -0.02658257;
          }
        }
      }
    } else {
      if ( (data[0].missing != -1) && (data[0].qvalue < 0)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 58)) {
          result[0] += -0.10541786;
        } else {
          result[0] += -0.029994424;
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 4)) {
            result[0] += 0.07427636;
          } else {
            result[0] += 0.013590855;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 34)) {
            result[0] += -0.1880994;
          } else {
            result[0] += 0.01300752;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 12)) {
    if ( (data[5].missing != -1) && (data[5].qvalue < 2)) {
      if ( (data[4].missing != -1) && (data[4].qvalue < 20)) {
        if ( (data[0].missing != -1) && (data[0].qvalue < 20)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 4)) {
            result[0] += -0.009752509;
          } else {
            result[0] += -0.014157267;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 8)) {
            result[0] += -0.034385912;
          } else {
            result[0] += -0.0035030486;
          }
        }
      } else {
        if ( (data[3].missing != -1) && (data[3].qvalue < 6)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 4)) {
            result[0] += -0.04247555;
          } else {
            result[0] += -0.0032594951;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
            result[0] += -0.08096939;
          } else {
            result[0] += 0.01836337;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 16)) {
        if ( (data[2].missing != -1) && (data[2].qvalue < 0)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 12)) {
            result[0] += 0.009610837;
          } else {
            result[0] += 0.10843191;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 14)) {
            result[0] += -0.007926232;
          } else {
            result[0] += 0.017779335;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 60)) {
            result[0] += -0.008509328;
          } else {
            result[0] += 0.01716882;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 30)) {
            result[0] += -0.017881393;
          } else {
            result[0] += -0.04348716;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 34)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 34)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
            result[0] += -0.015048607;
          } else {
            result[0] += 0.011351565;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 32)) {
            result[0] += -0.010020442;
          } else {
            result[0] += -0.1186176;
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 22)) {
          if ( (data[4].missing != -1) && (data[4].qvalue < 0)) {
            result[0] += -0.032271918;
          } else {
            result[0] += 0.011430915;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 42)) {
            result[0] += 0.12840088;
          } else {
            result[0] += -0.036743667;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 0)) {
        if ( (data[0].missing != -1) && (data[0].qvalue < 2)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 0)) {
            result[0] += -0.019260585;
          } else {
            result[0] += -0.08408626;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 36)) {
            result[0] += -0.04279659;
          } else {
            result[0] += -0.021065455;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 2)) {
            result[0] += 0.032873508;
          } else {
            result[0] += 0.0077392054;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 46)) {
            result[0] += -0.0014209503;
          } else {
            result[0] += -0.0677324;
          }
        }
      }
    }
  }
  if ( (data[2].missing != -1) && (data[2].qvalue < 24)) {
    if ( (data[0].missing != -1) && (data[0].qvalue < 42)) {
      if ( (data[2].missing != -1) && (data[2].qvalue < 18)) {
        if ( (data[4].missing != -1) && (data[4].qvalue < 46)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 4)) {
            result[0] += -0.0064325235;
          } else {
            result[0] += -0.0045092315;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 42)) {
            result[0] += -0.013254624;
          } else {
            result[0] += 0.025551753;
          }
        }
      } else {
        if ( (data[4].missing != -1) && (data[4].qvalue < 38)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 8)) {
            result[0] += -0.022071607;
          } else {
            result[0] += -0.0009896323;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 26)) {
            result[0] += -0.038525574;
          } else {
            result[0] += -0.010636883;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 34)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 4)) {
            result[0] += -0.009609639;
          } else {
            result[0] += 0.011474244;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 26)) {
            result[0] += -0.0063209175;
          } else {
            result[0] += -0.07679385;
          }
        }
      } else {
        if ( (data[1].missing != -1) && (data[1].qvalue < 22)) {
          if ( (data[2].missing != -1) && (data[2].qvalue < 18)) {
            result[0] += 0.02436176;
          } else {
            result[0] += 0.006384274;
          }
        } else {
          if ( (data[4].missing != -1) && (data[4].qvalue < 20)) {
            result[0] += -0.026487963;
          } else {
            result[0] += 0.02496786;
          }
        }
      }
    }
  } else {
    if ( (data[4].missing != -1) && (data[4].qvalue < 34)) {
      if ( (data[5].missing != -1) && (data[5].qvalue < 32)) {
        if ( (data[5].missing != -1) && (data[5].qvalue < 30)) {
          if ( (data[3].missing != -1) && (data[3].qvalue < 0)) {
            result[0] += -0.018074282;
          } else {
            result[0] += 0.0007337175;
          }
        } else {
          if ( (data[0].missing != -1) && (data[0].qvalue < 30)) {
            result[0] += 0.0025586407;
          } else {
            result[0] += -0.074166805;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 56)) {
          if ( (data[1].missing != -1) && (data[1].qvalue < 8)) {
            result[0] += 0.023081018;
          } else {
            result[0] += 0.0048284666;
          }
        } else {
          if ( (data[2].missing != -1) && (data[2].qvalue < 30)) {
            result[0] += -0.0018339517;
          } else {
            result[0] += -0.083369166;
          }
        }
      }
    } else {
      if ( (data[5].missing != -1) && (data[5].qvalue < 46)) {
        if ( (data[3].missing != -1) && (data[3].qvalue < 36)) {
          if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
            result[0] += 0.007805875;
          } else {
            result[0] += -0.0003558124;
          }
        } else {
          if ( (data[5].missing != -1) && (data[5].qvalue < 24)) {
            result[0] += -0.01568204;
          } else {
            result[0] += -0.11504749;
          }
        }
      } else {
        if ( (data[5].missing != -1) && (data[5].qvalue < 58)) {
          if ( (data[0].missing != -1) && (data[0].qvalue < 2)) {
            result[0] += 0.075817436;
          } else {
            result[0] += 0.008088254;
          }
        } else {
          if ( (data[3].missing != -1) && (data[3].qvalue < 38)) {
            result[0] += -0.11018554;
          } else {
            result[0] += -0.008356836;
          }
        }
      }
    }
  }
  
  // Apply base_scores
  result[0] += 0.5;
  
  // Apply postprocessor
  if (!pred_margin) { postprocess(result); }
}

void postprocess(float* result) {
  // Do nothing
}

