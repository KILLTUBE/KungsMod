void PM_VehicleImpact( bgEntity_t *pEnt, trace_t *trace );
qboolean PM_GroundSlideOkay( float zNormal );
qboolean PM_ClientImpact( trace_t *trace );
qboolean PM_SlideMove( qboolean gravity );
void PM_StepSlideMove( qboolean gravity );
