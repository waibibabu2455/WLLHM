// Find bounding box for triangle
    float minX = std::min({v[0].x(), v[1].x(), v[2].x()});
    float maxX = std::max({v[0].x(), v[1].x(), v[2].x()});
    float minY = std::min({v[0].y(), v[1].y(), v[2].y()});
    float maxY = std::max({v[0].y(), v[1].y(), v[2].y()});

//Iterate
    for(int x = minX;x<=maxX;x++){
        for(int y = minY;y<=maxY;y++){
            if(insideTriangle(x+0.5,y+0.5,t.v)){
                auto[alpha, beta, gamma] = computeBarycentric2D(x+0.5, y+0.5, t.v);
                float w_reciprocal = 1.0/(alpha/v[0].w()+beta/v[1].w()+gamma/v[2].w());
                float z_interpolated = alpha*v[0].z()/v[0].w()+beta*v[1].z()/v[1].w()+gamma*v[2].z()/v[2].w();
                z_interpolated*=w_reciprocal;
                //如果当前位置深度比depth_buf更小，则更新颜色值
                if(z_interpolated<depth_buf[get_index(x,y)]){
                    Eigen::Vector3f interpolated_color = interpolate(alpha,beta,gamma,t.color[0],t.color[1]*255,t.color[2]*255,1);
                    set_pixel(Vector2i(x, y), interpolated_color);
                    depth_buf[get_index(x,y)]=z_interpolated;
                    
                }
            }
        }
    }

