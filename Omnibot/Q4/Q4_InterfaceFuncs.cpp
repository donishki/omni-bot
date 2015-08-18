////////////////////////////////////////////////////////////////////////////////
//
// $LastChangedBy$
// $LastChangedDate$
// $LastChangedRevision$
//
////////////////////////////////////////////////////////////////////////////////

#include "Q4_InterfaceFuncs.h"

#include "BotWeaponSystem.h"

namespace InterfaceFuncs
{
	const char *GetLocation( const Vector3f &_pos )
	{
		Q4_Location data;
		data.mPosition[ 0 ] = _pos[ 0 ];
		data.mPosition[ 1 ] = _pos[ 1 ];
		data.mPosition[ 2 ] = _pos[ 2 ];
		data.mLocationName[ 0 ] = 0;
		MessageHelper msg( Q4_MSG_GETLOCATION, &data, sizeof( data ) );
		InterfaceMsg( msg );
		return data.mLocationName ? data.mLocationName : "";
	}

	float GetPlayerCash( const GameEntity _player )
	{
		Q4_PlayerCash data = { 0.0f };
		MessageHelper msg( Q4_MSG_GETPLAYERCASH, &data, sizeof( data ) );
		gEngineFuncs->InterfaceSendMessage( msg, _player );
		return data.mCash;
	}

	bool IsBuyingAllowed()
	{
		Q4_IsBuyingAllowed data = { False };
		MessageHelper msg( Q4_MSG_ISBUYINGALLOWED, &data, sizeof( data ) );
		InterfaceMsg( msg );
		return ( data.mBuyingAllowed == True );
	}

	bool BuySomething( const GameEntity _player, int _item )
	{
		Q4_ItemBuy data = { _item };
		MessageHelper msg( Q4_MSG_BUYSOMETHING, &data, sizeof( data ) );
		if ( !SUCCESS( InterfaceMsg( msg, _player ) ) )
		{
			LOGERR( "Invalid Item specified: " << _item );
		}
		return data.mSuccess == True;
	}
};