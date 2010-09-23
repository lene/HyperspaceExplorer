//
// C++ Interface: ViewImpl
//
// Description:
//
//
// Author: Helge Preuss <lene.preuss@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef VIEW_IMPL_H
#define VIEW_IMPL_H 1

#include "View.h"
#include "Light.h"

namespace UI {

    /// Interface with attributes to display four-dimensional objects
    /** This class provides a partial implementation of the class View, with
     *  the class attributes and their getters and setters.
     *
     *  It also stores view states, which are common to all implementations,
     *  such as:
     *      - The object which is currently displayed
     *      - The 4D transformation of that object
     *      - The 4D viewport (camera and screen position)
     *
     *  \ingroup UIGroup
     */
    class ViewImpl: public View {

        public:

            /// Initialize the View with default values for all states
            ViewImpl();

            /// \return The currently displayed object
            virtual const std::tr1::shared_ptr<Function> &F() const;
            /// Implementation of UI::View::setFunction
            virtual void setF(Function *_f);

            /// \return delta values in angles for 4D rotation for animations
            virtual const VecMath::Rotation<4> &getdR();
            /// Set the rotation step between frames for animations
            /** \param _dr Rotation step between two frames of an animation   */
            virtual void setdR(const VecMath::Rotation<4> &_dr);

            /// Set the number of frames for an animation
            virtual void setNumFrames(unsigned frames);
            /// Set the number of times \p _numFrames are repeated
            virtual void setNumLoops(unsigned loops);

            /// \return directory to save images to
            virtual const std::string &getImgDir();
            /// Set the directory where to store image files
            virtual void setImgDir(const std::string &);
            /// \return filename prefix for saved images
            virtual const std::string &getImgPrefix();
            /// Set the prefix of image file names, before the frame number and the extension
            virtual void setImgPrefix(const std::string &);

            /// \return The background color
            virtual const Color &getBackground();
            /// Set the background color
            virtual void setBackground(const Color &bg);

            /// Add a light source to the scene
            /** \param l Light source added to the scene */
            virtual void addLight(Light *l);
            /// Remove a light source from the scene
            virtual void removeLight(std::vector<Light *>::iterator);
            /// \return All lights in the scene
            /** \todo Abstract from std::vector and use a generic container */
            virtual const std::vector<Light *> &getLights();

            /// \return whether to use colors in rendering or not
            virtual bool getColors() const;
            /// Turn display of colors on or off
            virtual void setColors(bool on);

            /// \return whether to display the 4D coordinate cross or not
            virtual bool getCoordinates() const;
            /// Turn display of coordinate cross on or off
            virtual void setCoordinates(bool on);

            /// \return whether to use depth cue/fog in rendering or not
            virtual bool getFog() const;
            /// Turn depth cue on or off
            virtual void setFog(bool on);

            /// \return whether to use four-dimensional depth cue or not
            virtual bool getHyperfog() const;
            /// Turn depth cue in four dimensions on or off
            virtual void setHyperfog(bool on);

            /// \return whether to use lighting in rendering or not
            virtual bool getLighting() const;
            /// Turn lighting on or off
            virtual void setLighting(bool on);

            /// \return whether to use shading in rendering or not
            virtual bool getShading() const;
            /// Turn gouraud shading on or off
            virtual void setShading(bool on);

            /// \return whether to draw the objects' surfaces
            virtual bool getSolid() const;
            /// Turn wireframe display on or off
            /** \param on if true, displays wireframe model; else solid       */
            virtual void setSolid(bool on);

            /// \return whether to use transparence/line antialiasing or not
            virtual bool getTransparence() const;
            /// Turn transparence/line antialiasing on or off
            virtual void setTransparence(bool on);

            /// drawTriangle() is a convenience function that may not be implemented in all Views - this implementation throws an exception
            virtual void drawTriangle(const VecMath::Vector< 4 >&, const VecMath::Vector< 4 >&, 
                                      const VecMath::Vector< 4 >&, 
                                      const VecMath::Vector< 3 >&, const VecMath::Vector< 3 >&, 
                                      const VecMath::Vector< 3 >&);
            /// drawPolygon() is a convenience function that may not be implemented in all Views - this implementation throws an exception
            virtual void drawPolygon(const std::vector< VecMath::Vector< 4 > >&, 
                                     const std::vector< VecMath::Vector< 3 > >&);

            virtual void drawCube(const VecMath::NestedVector< VecMath::Vector< 4 >, 3 >& X, 
                                  unsigned int t, unsigned int u, unsigned int v, 
                                  const VecMath::Vector< 3 >& v0, const VecMath::Vector< 3 >& v1, 
                                  const VecMath::Vector< 3 >& v2, const VecMath::Vector< 3 >& v3, 
                                  const VecMath::Vector< 3 >& v4, const VecMath::Vector< 3 >& v5,
                                  const VecMath::Vector< 3 >& v6, const VecMath::Vector< 3 >& v7);
            
        protected:

            /// Number of frames for animations
            virtual unsigned getNumFrames();
            /// Number of loops to repeat an animation
            virtual unsigned getNumLoops();

            /// \return whether to save images to file system
            virtual bool getWriteImages();
            /// Turn saving images to file system on or off
            virtual void setWriteImages(bool on);

            /// Set a default background color
            virtual void setDefaultBackground();

            /// \param _t New translation state
            virtual void setT(const VecMath::Vector<4> &_t);
            /// \return Current translation state
            virtual const VecMath::Vector<4> &T();
            /// Add a Translation to the current translation state
            /** \param _dT Delta t */
            virtual void addT(const VecMath::Vector<4> &_dT);

            /// \param _r New rotation state
            virtual void setR(const VecMath::Rotation<4> &_r);
            /// \return Current rotation state
            virtual const VecMath::Rotation<4> &R();
            /// Add a Rotation to the current rotation state
            virtual void addR(const VecMath::Rotation<4> &_dR);

            /// Add a Rotation to the current rotation speed
            virtual void adddR(const VecMath::Rotation<4> &);

            /// \return W coordinate of the camera
            double CamW() const;
            /// \param _cw W coordinate of the camera
            void setCamW(const double &_cw);
            /// \return W coordinate of the screen to project onto
            double ScrW() const;
            /// \param _sw W coordinate of the screen to project onto
            void setScrW(const double &_sw);

            /// Viewport distance; currently fixed to 1
            double distance();

            /// \return Point LightSource with sensible defaults for good light
            static const LightSource &getDefaultLightSource();
            /// \return LightSource for flat, all-ambient lighting
            static const LightSource &getFlatLightSource();

        private:

            class Impl;
            
            Impl *pImpl_;

            /// Default Color for the background
            static Color _defaultBackground;

            /// Point LightSource with sensible defaults for good light
            static LightSource _defaultLightSource;
            /// LightSource for flat, all-ambient lighting
            static LightSource _flatLightSource;
        
    };

}

#endif
