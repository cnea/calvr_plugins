#ifndef FP_GRAPH_LAYOUT_OBJECT_H
#define FP_GRAPH_LAYOUT_OBJECT_H

#include <cvrKernel/TiledWallSceneObject.h>
#include <cvrMenu/MenuButton.h>
#include <cvrMenu/MenuCheckbox.h>
#include <cvrMenu/MenuRangeValueCompact.h>
#include <cvrInput/TrackerBase.h>

#include "GraphObject.h"
#include "MicrobeGraphObject.h"
#include "MicrobeBarGraphObject.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgText/Text>

#include <ctime>
#include <vector>
#include <map>

class GraphLayoutObject : public cvr::TiledWallSceneObject
{
    public:
        GraphLayoutObject(float width, float height, int maxRows, std::string name, bool navigation, bool movable, bool clip, bool contextMenu, bool showBounds=false);
        virtual ~GraphLayoutObject();

        void addGraphObject(LayoutTypeObject * object);
        void removeGraphObject(LayoutTypeObject * object);

        void selectMicrobes(std::string & group, std::vector<std::string> & keys);

        void removeAll();
        void perFrame();

        void minimize();
        void maximize();
        bool isMinimized()
        {
            return _minimized;
        }

        void setRows(float rows);
        void setSyncTime(bool sync);

        bool dumpState(std::ostream & out);
        bool loadState(std::istream & in);

        virtual void menuCallback(cvr::MenuItem * item);

        virtual bool processEvent(cvr::InteractionEvent * event);
        virtual void enterCallback(int handID, const osg::Matrix &mat);
        virtual void updateCallback(int handID, const osg::Matrix &mat);
        virtual void leaveCallback(int handID);
    protected:
        void makeGeometry();
        void updateGeometry();
        void updateLayout();

        bool loadObject(std::istream & in);

        bool _minimized;

        std::vector<LayoutTypeObject *> _objectList;
        std::map<LayoutTypeObject *,cvr::MenuButton *> _deleteButtonMap;

        std::string _currentSelectedMicrobeGroup;
        std::vector<std::string> _currentSelectedMicrobes;

        float _width;
        float _height;
        int _maxRows;

        time_t _maxX;
        time_t _minX;
        time_t _currentMaxX;
        time_t _currentMinX;

        osg::ref_ptr<osg::Geode> _layoutGeode;
        osg::ref_ptr<osg::Vec3Array> _verts;
        osg::ref_ptr<osgText::Text> _text;

        cvr::MenuButton * _resetLayoutButton;
        cvr::MenuButton * _minmaxButton;
        cvr::MenuCheckbox * _syncTimeCB;
        cvr::MenuCheckbox * _zoomCB;
        cvr::MenuRangeValueCompact * _rowsRV;
        cvr::MenuRangeValueCompact * _widthRV;
        cvr::MenuRangeValueCompact * _heightRV;

        int _activeHand;
        cvr::TrackerBase::TrackerType _activeHandType;

        std::vector<int> _perGraphActiveHand;
        std::vector<cvr::TrackerBase::TrackerType> _perGraphActiveHandType;
};

#endif
