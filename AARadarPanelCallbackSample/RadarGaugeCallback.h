#pragma once

#include "gauges.h"
#include "ISimulatedRadar.h"
#include "NetInOutPublic.h"

#include "Properties.h"


namespace Radar
{
	//
	// Class that implements IGaugeCCallback
	//
	class RadarGaugeCallback : public ISerializableGaugeCCallback
	{
		DECLARE_PANEL_CALLBACK_REFCOUNT(P3DRADARGaugeCallback);

	public:
		GAUGE_CALLBACK gauge_callback;

		RadarGaugeCallback(UINT32 containerId, ISimulatedRadarV400* pRadar);

		// ************* IGaugeCCallback Methods ***************
		bool GetPropertyValue(SINT32 id, FLOAT64* pValue);
		bool SetPropertyValue(SINT32 id, FLOAT64 value);

		// **** IGaugeCCallback Methods Not being used by this implementation ****
		IGaugeCCallback* QueryInterface(LPCSTR pszInterface);
		void Update() {               }
		bool GetPropertyValue(SINT32 id, LPCSTR* pszValue) { return false; }
		bool SetPropertyValue(SINT32 id, LPCSTR szValue) { return false; }
		bool GetPropertyValue(SINT32 id, LPCWSTR* pszValue) { return false; }
		bool SetPropertyValue(SINT32 id, LPCWSTR szValue) { return false; }
		IGaugeCDrawable* CreateGaugeCDrawable(SINT32 id, const IGaugeCDrawableCreateParameters* pParameters) { return nullptr; }

		// Note: As of Prepar3D 2.3 these will get called on flight load/save in addition to the original shared cockpit use case.
		bool Serialize(NetOutPublic& netout);
		bool Deserialize(NetInPublic& netin);

	protected:
		// Because this callback acts as a pass-though to the radar system serialization is a bit more complex than the general case.
		// Where all the property values are stored in member variables that can be written out and read in. 
		// Because of this an internal struct is used to wrap the serialization data. 

		// use a magic value as the radar header
#define RADAR_CALLBACK_SERIALIZATION_HEADER_ID 0xffa41af2
// include a version number in case this plug-in gets a new version that
// needs to serialize more data
#define RADAR_CALLBACK_SERIALIZATION_VERSIONS 1
		struct RadarGaugeSerializationData
		{
			struct DataHeader
			{
				DataHeader() : HeaderID(RADAR_CALLBACK_SERIALIZATION_HEADER_ID),
					SizeInBytes(sizeof(RadarGaugeSerializationData)),
					Version(RADAR_CALLBACK_SERIALIZATION_VERSIONS)
				{ }
				// Check the magic value against the define above to make sure the this plugin has data to load
				bool IsValid()           const { return (HeaderID == RADAR_CALLBACK_SERIALIZATION_HEADER_ID); }
				// Check version to make sure it is the same
				bool IsCurrentVersion()  const { return (Version == RADAR_CALLBACK_SERIALIZATION_VERSIONS); }
				// Check size of data stored
				bool ValidateSize()      const { return SizeInBytes == sizeof(RadarGaugeSerializationData); }
				unsigned long HeaderID;
				int SizeInBytes;
				int Version;
			};

			DataHeader Header;
			bool ShowRangeRings;
			bool ShowCursor;
			bool FarShoreEnhance;
			double VisualZoom;
			double DataZoom;
			double ScanAzimuth;
			double SweepRate;
			double RangeMiles;
			bool RenderingEnabled;
			double CursorPositionX;
			double CursorPositionY;
			bool FreezeEnabled;
			double FrontBlindspotDegrees;
			double SideBlindspotDegrees;
			double RadarResolutionX;
			double RadarResolutionY;
			double GaugeResolutionX;
			double GaugeResolutionY;
		};

		~RadarGaugeCallback();
	private:
		bool   m_bRadarNeedsDeinit;
		UINT32 m_containerId;
		ISimulatedRadarV400* m_pRadar;
	};

}