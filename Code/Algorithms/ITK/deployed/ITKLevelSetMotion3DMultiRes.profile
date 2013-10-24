SET(ALGORITHM_PROFILE_UID_Namespace "de.dkfz.matchpoint.itk")
SET(ALGORITHM_PROFILE_UID_Name "LevelSetMotion.3D.multiRes.default")
SET(ALGORITHM_PROFILE_UID_Version "1.0.0")

SET(ALGORITHM_PROFILE_Description "Deformable 3D registration algorithm based on an level set motion approach and using a 4 level multi resolution approach to get faster and more robust results. This algorithm is only suitable for mono modal tasks.")
SET(ALGORITHM_PROFILE_Contact "Ralf Floca\; sbr@dkfz-heidelberg.de")
SET(ALGORITHM_PROFILE_Citation "B.C. Vemuri, J. Ye, Y. Chen, C.M. Leonard.: Image registration via level-set motion: applications to atlas-based segmentation. Medical Image Analysis. Vol. 7. pp. 1-20. 2003.")

SET(ALGORITHM_PROFILE_DataType "Image")
SET(ALGORITHM_PROFILE_ResolutionStyle "4 (multi res)")
SET(ALGORITHM_PROFILE_DimMoving "3")
SET(ALGORITHM_PROFILE_ModalityMoving "any/monomodal")
SET(ALGORITHM_PROFILE_DimTarget "3")
SET(ALGORITHM_PROFILE_ModalityTarget "any/monomodal")
SET(ALGORITHM_PROFILE_Subject "any")
SET(ALGORITHM_PROFILE_Object "any")
SET(ALGORITHM_PROFILE_TransformModel "deformable")
SET(ALGORITHM_PROFILE_TransformDomain "lokal")
SET(ALGORITHM_PROFILE_Metric "Mean square difference")
SET(ALGORITHM_PROFILE_Keywords "deformable" "monomodal" "multi resolution")
